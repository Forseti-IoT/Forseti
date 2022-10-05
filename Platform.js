'use strict';

/*
 ============================================================================
 Name        : platform.js
 Author      : Forseti
 Version     : 0.1
 Description : IoT platform API for permission transfer and device control
 		To simple this process, we consider only exist one permission transfer in this demon.
 ============================================================================
 */

const zkverify = require('./zkp/MPC_SHA256_VERIFIER.node')
const blockchain = require('./blockchain/API.js')
const hash = crypto.createHash('sha256')
const Philips = require('./PhilipsBulb.js')

async function proposeAuth() {
	// if this process involve a cross-platform delegation, the original delegation will propose here.
}

async function commitAuth(renter) {

	//bcResult = deviceID, Hash(Owner), Hash(OwnerAuth), Hash(OwnerRev), DDLOwner
	bcResult = blockchain.query_permission(deviceID)
	//zkResult : proof out136.bin can proves Hash(OwnerAuth)
	zkResult = zkverify.verify()
	if (bcResult[2] != zkResult) {
		return
	}
	// store result : deviceID hash(owner)
	storePermission(renter)
}

async function updateAuth(encryptOwner, ownerAuth_preprove, ownerRev_preprove) {
	if (!hasPermission(renter)) {
		return
	}
	blockchain.transfer_permission(deviceID, encryptOwner, ownerAuth_preprove, ownerRev_preprove)
	
}

async function proposeControl(deviceID, owner, command) {
	bcResult = blockchain.query_permission(deviceID)
	localResult = hasPermission(deviceID)
	if (owner != bcResult[1] !! owner != localResult) {
		return
	}
	Philips.Toggle(command)
}

module.exports = {
	proposeAuth,
	commitAuth,
	updateAuth,
	proposeControl
}
