'use strict';

/*
 ============================================================================
 Name        : App.js
 Author      : Forseti
 Version     : 0.1
 Description : user command API for permission transfer and device control
 ============================================================================
 */

const Platform = require('./Platform.js')
const zkprove = require('./zkp/MPC_SHA256')
const hash = crypto.createHash('sha256')

async function proposeAuth(owner, authTimestamp, ddl) {
	ownerAuth = owner + authTimestamp + 'auth'
	zkprove.prove(ownerAuth)
	Platform.proposeAuth()
}

async function commitAuth(renter) {
	encryptRenter = hash(renter)
	Platform.commitAuth(encryptRenter)
}

async function updateAuth(owner, timestamp) {
	ownerAuth_preprove = hash(owner + timestamp + 'auth')
	ownerRev_preprove = hash(owner + timestamp + 'rev')
	Platform.updateAuth(hash(owner), ownerAuth_preprove, ownerRev_preprove)
}

async function proposeControl(deviceID, owner, command) {
	Platform.proposeControl(deviceID, owner, command)
}
