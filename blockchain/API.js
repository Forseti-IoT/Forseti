'use strict';
//SAMPLE_APIKEY=$(grep ORG1_APIKEY .env | cut -d '=' -f 2-) ->API_KEY
const API_KEY = "29e5f8a6-bf5c-468f-b604-031def36cebe"
const BlockchainHost= "192.168.123.181"
const http = require('http')
const co = require('co')
//const crypto = require('crypto')
//const hash = crypto.createHash('sha256')
//const querystring = require('querystring');  


async function http_request(path, method, headers, post_data = '') {
	var data = ''
	var options = {
		hostname: BlockchainHost,
		port: 3000,
		path: path,
		method: method,
		headers: headers,
	}
	
	return new Promise((resolve, reject) =>{ 
		const req = http.request(options, res => {
			//var data = []
			
			console.log(res.statusCode)
			res.on('data', d => {
				data += d 
			})
				
			res.on('end', () => {
				resolve({result: true, data: data});
			})
		})
	

		req.on('error', (e) => {
			resolve({result:false, errmsg: e.message});
		})
		if (method == 'POST') {
			//var content = querystring.stringify(post_data)
			req.write(post_data)
		}
		req.end()
	})
	
}

async function query_permission(deviceID) {
	var path = '/api/assets/'+deviceID
	var headers = {
		'X-Api-Key': API_KEY,
	}
	
	try {

		var res = await http_request(path, 'GET', headers)
		var owner = JSON.parse(res.data).Owner
		console.log(owner);
		return owner

	} catch (error) {
		console.log(error)
	}
}

async function register_permission(deviceID, owner) {
	var path = '/api/assets'
	var headers = {
		'X-Api-Key': API_KEY,
		'Content-Type': 'application/json',
	}
	var post_data = JSON.stringify({  
		'ID' : deviceID,
		'Owner': owner
	})
	try {

		var res = await http_request(path, 'POST', headers, post_data)
		var owner = JSON.parse(res.data).Owner
		console.log(owner);
		return owner

	} catch (error) {
		console.log(error)
	}
}

function transfer_permission(deviceID, encryptedRenter, platformSign) {

}

module.exports = {
	query_permission,
	register_permission,
	transfer_permission
}
