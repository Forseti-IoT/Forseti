/*
 ============================================================================
 Name        : MPC_SHA256_VERIFIER.c
 Description : Verifies a proof for SHA-256 generated by MPC_SHA256.c
 ============================================================================
 */

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "shared.h"
#include <node_api.h>
#include <assert.h>

#define NAPI_CALL(env, call)                                      \
  do {                                                            \
    napi_status status = (call);                                  \
    if (status != napi_ok) {                                      \
      const napi_extended_error_info* error_info = NULL;          \
      napi_get_last_error_info((env), &error_info);               \
      const char* err_message = error_info->error_message;        \
      bool is_pending;                                            \
      napi_is_exception_pending((env), &is_pending);              \
      if (!is_pending) {                                          \
        const char* message = (err_message == NULL)               \
            ? "empty error message"                               \
            : err_message;                                        \
        napi_throw_error((env), NULL, message);                   \
        return NULL;                                              \
      }                                                           \
    }                                                             \
  } while(0)

int NUM_ROUNDS = 136;
char res[64];

void printbits(uint32_t n) {
	if (n) {
		printbits(n >> 1);
		printf("%d", n & 1);
	}

}



char* do_verifyRes(void) {
	setbuf(stdout, NULL);
	init_EVP();
	openmp_thread_setup();
	
	//printf("Iterations of SHA: %d\n", NUM_ROUNDS);

	//clock_t begin = clock(), delta, deltaFiles;
	
	a as[NUM_ROUNDS];
	z zs[NUM_ROUNDS];
	FILE *file;

	char outputFile[3*sizeof(int) + 8];
	sprintf(outputFile, "out%i.bin", NUM_ROUNDS);
	file = fopen(outputFile, "rb");
	if (!file) {
		//printf("Unable to open file!");
		//fclose(file);
		openmp_thread_cleanup();
		cleanup_EVP();
		return "";
	}
	fread(&as, sizeof(a), NUM_ROUNDS, file);
	fread(&zs, sizeof(z), NUM_ROUNDS, file);
	fclose(file);
	
	uint8_t *res_raw[64];
	//char res[64];
	uint32_t y[8];
	reconstruct(as[0].yp[0],as[0].yp[1],as[0].yp[2],y);
	//printf("Proof for hash: ");
	for(int i=0;i<8;i++) {
		res_raw[8*i]     = y[i] >> 28 & 0xf;
		res_raw[8*i + 1] = y[i] >> 24 & 0xf;
		res_raw[8*i + 2] = y[i] >> 20 & 0xf;
		res_raw[8*i + 3] = y[i] >> 16 & 0xf;
		res_raw[8*i + 4] = y[i] >> 12 & 0xf;
		res_raw[8*i + 5] = y[i] >>  8 & 0xf;
		res_raw[8*i + 6] = y[i] >>  4 & 0xf;
		res_raw[8*i + 7] = y[i] >>  0 & 0xf;
		//printf("This:%02X, %X, %X, %X, %X, %X, %X, %X, %X ", y[i], res_raw[8*i], res_raw[8*i+1], res_raw[8*i+2], res_raw[8*i+3],  res_raw[8*i+4], res_raw[8*i+5], res_raw[8*i+6], res_raw[8*i+7]);
		//printf("%02X", y[i]);
	}
	//printf("\n and current test is \n");

	for (int i = 0; i < 64; i++) {
		if (res_raw[i] < 10) {
			res[i] = res_raw[i] + '0';
		}
		else {
			res[i] = res_raw[i] - 10 + 'A';
		}
		//printf("%c",res[i]);
	}
	//printf("\n");

	//deltaFiles = clock() - begin;
	//int inMilliFiles = deltaFiles * 1000 / CLOCKS_PER_SEC;
	//printf("Loading files: %ju\n", (uintmax_t)inMilliFiles);


	//clock_t beginE = clock(), deltaE;
	int es[NUM_ROUNDS];
	H3(y, as, NUM_ROUNDS, es);
	//deltaE = clock() - beginE;
	//int inMilliE = deltaE * 1000 / CLOCKS_PER_SEC;
	//printf("Generating E: %ju\n", (uintmax_t)inMilliE);


	//clock_t beginV = clock(), deltaV;
	#pragma omp parallel for
	for(int i = 0; i<NUM_ROUNDS; i++) {
		int verifyResult = verify(as[i], es[i], zs[i]);
		if (verifyResult != 0) {
			//printf("Not Verified %d\n", i);
			
		}
	}
	//deltaV = clock() - beginV;
	//int inMilliV = deltaV * 1000 / CLOCKS_PER_SEC;
	//printf("Verifying: %ju\n", (uintmax_t)inMilliV);
	
	
	//delta = clock() - begin;
	//int inMilli = delta * 1000 / CLOCKS_PER_SEC;

	//printf("Total time: %ju\n", (uintmax_t)inMilli);
	



	openmp_thread_cleanup();
	cleanup_EVP();
	for (int i = 0; i < 64; i++) {
		//printf("%c",res[i]);
	}
	//printf("\n");
	return res;
	//return EXIT_SUCCESS;
}

napi_value verifyRes(napi_env env, napi_callback_info info) {
	napi_status status;
	napi_value res;
	//status = napi_create_string_utf8(env, do_verifyRes(), NAPI_AUTO_LENGTH, &res);
	//assert(status == napi_ok);
	NAPI_CALL(env, napi_create_string_utf8(env, do_verifyRes(), 64, &res));
	return res;
}

napi_value Init(napi_env env, napi_value exports)
{
    //napi_status status;
    napi_property_descriptor descriptor = {
    	"verifyRes",
    	0,
    	verifyRes,
    	0,
    	0,
    	0,
    	napi_default,
    	0,
    };
    NAPI_CALL(env, napi_define_properties(env, exports, 1, &descriptor));
    //status = napi_define_properties(env, exports, 1, &descriptor);
    //assert(status == napi_ok);
    
    //napi_value fn;
    //status = napi_create_function(env, NULL, 0, verifyRes, NULL, &fn);
    //if (status != napi_ok)
        //return NULL;

    //status = napi_set_named_property(env, exports, "verifyRes", fn);
    //if (status != napi_ok)
        //return NULL;

    return exports;
}

NAPI_MODULE(NODE_GYP_MODULE_NAME, Init)