#include <pebble.h>

#include "windows/auth_handler.h"
#include "windows/start_menu.h"

static void init() { 
  start_menu_push(); 
}

static void deinit() {}

int main(void) {
  init();
  app_event_loop();
  deinit();
}