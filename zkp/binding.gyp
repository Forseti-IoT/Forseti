{
    "targets": [{
        "target_name": "MPC_SHA256_VERIFIER",
        "sources": ["./MPC_SHA256_VERIFIER.c"],
        "cflags": ["-lssl",
        	"-lcrypto",
        	"-fopenmp"
        ],
        "libraries": [
        	"/usr/lib/x86_64-linux-gnu/libgomp.so.1"
        ]
    },
    {
        "target_name": "MPC_SHA256",
        "sources": ["./MPC_SHA256.c"],
        "cflags": ["-lssl",
        	"-lcrypto",
        	"-fopenmp"
        ],
        "libraries": [
        	"/usr/lib/x86_64-linux-gnu/libgomp.so.1"
        ]
    }]
}
