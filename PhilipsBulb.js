'use strict';

const axios = require('axios');
const path = require('path');
const https = require('https');

const httpsAgent = new https.Agent({rejectUnauthorized: false});

var hueToken='hL2sEM2bGwgat9dtKXgjLooiJMPnzz9yKr8YRonW'
var hueAPI = 'https://192.168.123.223/api/'+hueToken+'/lights/12'

function Toggle(command) {
	axios.put(hueAPI+'/state', 
	  { on: false },
	  { httpsAgent }
	  )
	  .then(function (response) {
	    console.log(response.data);
	  })
	  .catch(function (error) {
	    console.log(error.data);
	  });
}
