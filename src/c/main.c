#include <pebble.h>

static Window *s_main_window;
static ScrollLayer *s_scroll_layer;
static TextLayer *s_text_layer;

static void main_window_load(Window *window) {
  Layer *window_layer = window_get_root_layer(window);
  GRect bounds = layer_get_bounds(window_layer);

  GFont font = fonts_get_system_font(FONT_KEY_GOTHIC_28_BOLD);

  // Find the bounds of the scrolling text
  GRect shrinking_rect = GRect(0, 0, bounds.size.w, 3000);
  char *text = "Example text that is really really really really really \
                                really really really really really really long really really really really really really long really really really really really really long really really really really really really long really really really really really really long really really really really really really long really really really really really really long really really really really really really long really really really really really really long really really really really really really long really really really really really really long really really really really really really long really really really really really really long really really really really really really long really really really really really really long really really really really really really long really really really really really really long really really really really really really long really really really really really really long really really really really really really long really really really really really really long really really really really really really long really really really really really really long really really really really really really long really really really really really really long really really really really really really long really really really really really really long really really really really really really long really really really really really really long really really really really really really long really really really really really really long really really really really really really long really really really really really really long really really really really really really long really really really really really really long really really really really really really long really really really really really really long really really really really really really long really really really really really really long really really really really really really long really really really really really really long really really really really really really long really really really really really really long really really really really really really long really really really really really really long really really really really really really long really really really really really really long really really really really really really long really really really really really really long really really really really really really long really really really really really really long really really really really really really long really really really really really really long really really really really really really long really really really really really really long really really really really really really long really really really really really really long really really really really really really long really really really really really really long really really really really really really long really really really really really really long really really really really really really long really really really really really really long really really really really really really long really really really really really really long really really really really really really long really really really really really really long really really really really really really long really really really really really really long really really really really really really long really really really really really really long really really really really really really long really really really really really really long really really really really really really long really really really really really really long really really really really really really long really really really really really really long really really really really really really long really really really really really really long really really really really really really long really really really really really really long really really really really really really long really really really really really really long really really really really really really long really really really really really really long really really really really really really long really really really really really really long really really really really really really long really really really really really really long really really really really really really long really really really really really really long really really really really really really long really really really really really really long really really really really really really long really really really really really really long really really really really really really long really really really really really really long really really really really really really long really really really really really really long ";
  GSize text_size = graphics_text_layout_get_content_size(text, font, 
                  shrinking_rect, GTextOverflowModeWordWrap, GTextAlignmentLeft);
  GRect text_bounds = bounds;
  text_bounds.size.h = text_size.h;

  // Create the TextLayer
  s_text_layer = text_layer_create(text_bounds);
  text_layer_set_overflow_mode(s_text_layer, GTextOverflowModeWordWrap);
  text_layer_set_font(s_text_layer, font);
  text_layer_set_text(s_text_layer, text);

  // Create the ScrollLayer
  s_scroll_layer = scroll_layer_create(bounds);

  // Set the scrolling content size
  scroll_layer_set_content_size(s_scroll_layer, text_size);

  // Let the ScrollLayer receive click events
  scroll_layer_set_click_config_onto_window(s_scroll_layer, window);

  // Add the TextLayer as a child of the ScrollLayer
  scroll_layer_add_child(s_scroll_layer, text_layer_get_layer(s_text_layer));

  // Add the ScrollLayer as a child of the Window
  layer_add_child(window_layer, scroll_layer_get_layer(s_scroll_layer));

}

static void main_window_unload(Window *window) {
  scroll_layer_destroy(s_scroll_layer);
  text_layer_destroy(s_text_layer);
}

static void init() {
  // Create main Window element and assign to pointer
  s_main_window = window_create();

  // Set the background color
  window_set_background_color(s_main_window, GColorWhite);

  // Set handlers to manage the elements inside the Window
  window_set_window_handlers(s_main_window, (WindowHandlers) {
    .load = main_window_load,
    .unload = main_window_unload
  });

  // Show the Window on the watch, with animated=true
  window_stack_push(s_main_window, true);
}

static void deinit() {
  // Destroy Window
  window_destroy(s_main_window);
}

int main(void) {
  init();
  app_event_loop();
  deinit();
}