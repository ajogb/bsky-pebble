#include "comms.h"
#include <pebble.h>

static bool s_js_ready;

bool comms_is_js_ready() { return s_js_ready; }

static void comms_inbox_received_callback(DictionaryIterator *iter, void *context) {
  Tuple *ready_tuple = dict_find(iter, MESSAGE_KEY_jsReady);
  if (ready_tuple) {
    // PebbleKit JS is ready! Safe to send messages
    s_js_ready = true;
    APP_LOG(APP_LOG_LEVEL_INFO,"Ready message recieved from pkjs");
  }
}

static void comms_inbox_dropped_callback(AppMessageResult reason,
                                         void *context) {
  // A message was received, but had to be dropped
  APP_LOG(APP_LOG_LEVEL_ERROR, "Message dropped. Reason: %d", (int)reason);
}

static void comms_outbox_sent_callback(DictionaryIterator *iter,
                                       void *context) {
  // The message just sent has been successfully delivered
}

static void comms_outbox_failed_callback(DictionaryIterator *iter,
                                         AppMessageResult reason,
                                         void *context) {
  // The message just sent failed to be delivered
  APP_LOG(APP_LOG_LEVEL_ERROR, "Message send failed. Reason: %d", (int)reason);
}

void comms_app_message_start(void) {
  app_message_register_inbox_received(comms_inbox_received_callback);
  app_message_register_inbox_dropped(comms_inbox_dropped_callback);
  app_message_register_outbox_sent(comms_outbox_sent_callback);
  app_message_register_outbox_failed(comms_outbox_failed_callback);

  app_message_open(BOX_SIZE, BOX_SIZE);
}