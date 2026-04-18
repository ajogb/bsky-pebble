Pebble.addEventListener("ready", function () {
  // PebbleKit JS is ready!
  console.log("PebbleKit JS ready!");

  Pebble.sendAppMessage({ jsReady: 1 });
});
