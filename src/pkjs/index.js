var Clay = require("@rebble/clay");
var clayConfig = require("./config");
var clay = new Clay(clayConfig);

let USER_ID;
let APP_PASSWORD;
let auth_token;
let auth_refresh_token;
let did;
let handle;


//xhr request helper
var xhrRequest = function (url, type, headers, body = null, callback) {
  var xhr = new XMLHttpRequest();
  xhr.open(type, url);
  for (var key in headers) {
    xhr.setRequestHeader(key, headers[key]);
  }
  xhr.onload = function () {
    callback(this.responseText);
  };
  xhr.send(body);
};

function auth() {
  let url = "https://bsky.social/xrpc/com.atproto.server.createSession";
  console.log("reading settings");
  let settings = JSON.parse(localStorage.getItem("clay-settings") || "{}");
  USER_ID = settings.C_USER_ID;
  APP_PASSWORD = settings.C_APP_PASSWORD;
  if (USER_ID == null || APP_PASSWORD == null) {
    console.log(
      "ERROR: Username and/or password not defined in phone settings"
    );
  } else {
    let headers = { "Content-Type": "application/json" };
    let body = { identifier: USER_ID, password: APP_PASSWORD };
    let authReq = new xhrRequest(
      url,
      "POST",
      headers,
      JSON.stringify(body),
      function (e) {
        console.log(e);
        let auth_token = e.accessJwt;
        let auth_refresh_token = e.refreshJwt;
        let did = e.did;
        let handle = e.handle;
        console.log(auth_token,auth_refresh_token,"\n",did,handle);

      }
    );
  }
}

Pebble.addEventListener("ready", function () {
  // PebbleKit JS is ready!
  console.log("PebbleKit JS ready!");

  Pebble.sendAppMessage({ JSREADY: 1 });
  let response = auth();
  console.log(response);
});
