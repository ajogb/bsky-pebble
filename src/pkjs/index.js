var Clay = require('@rebble/clay');
var clayConfig = require('./config');
var clay = new Clay(clayConfig);

let C_USER_ID;
let C_APP_PASSWORD;

//xhr request helper
var xhrRequest = function (url, type, callback) {
  var xhr = new XMLHttpRequest();
  xhr.onload = function () {
    callback(this.responseText);
  };
  xhr.open(type, url);
  xhr.send();
};

function auth() {
  console.log('reading settings');
  let settings = JSON.parse(localStorage.getItem('clay-settings') || '{}');
  console.log(settings.C_APP_PASSWORD);
}

Pebble.addEventListener("ready", function () {
  // PebbleKit JS is ready!
  console.log("PebbleKit JS ready!");

  Pebble.sendAppMessage({ JSREADY: 1 });
  auth();
});
