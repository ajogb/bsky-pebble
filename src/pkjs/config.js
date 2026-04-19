module.exports = [
  {
    "type": "heading",
    "defaultValue": "Butterfly Settings"
  },
  {
    "type": "section",
    "items": [
      {
        "type": "heading",
        "defaultValue": "Login"
      },
      {
        "type": "input",
        "messageKey": "C_USER_ID",
        "defaultValue": "",
 "label": "Username"
      },
      {
        "type": "input",
        "messageKey": "C_APP_PASSWORD",
        "defaultValue": "",
        "label": "App Password",
        "description": "Get an app password from Bluesky settings > Privacy and security > App passwords"
      }
    ]
  },
  {
    "type": "submit",
    "defaultValue": "Save Settings"
  }
];
