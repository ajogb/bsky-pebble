#include <pebble.h>

#include "windows/auth_handler.h"
#include "windows/start_menu.h"
#include "modules/comms.h"

static void init() { 
  start_menu_push();
  comms_app_message_start();
}

static void deinit() {
  app_message_deregister_callbacks();
}

int main(void) {
  init();
  app_event_loop();
  deinit();
}