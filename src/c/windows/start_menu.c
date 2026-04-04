#include "start_menu.h"

#define NUM_ROWS 3

static Window *s_window_start;
static MenuLayer *s_menu_layer;

// static SimpleMenuItem items[] = {{.title = "Following"}, {.title = "Feeds"}};

// static SimpleMenuSection main_section = {
//     .title = "Butterfly", .items = items, .num_items = 2};

static uint16_t get_num_rows_callback(MenuLayer *menu_layer,
                                      uint16_t section_index, void *context) {
  const uint16_t num_rows = NUM_ROWS;
  return num_rows;
}

static void draw_row_callback(GContext *ctx, const Layer *cell_layer,
                              MenuIndex *cell_index, void *context) {
  switch (cell_index->row) {
  case 0:
    menu_cell_title_draw(ctx, cell_layer, "Butterfly");
    break;
  case 1:
    menu_cell_basic_draw(ctx, cell_layer, "Following", NULL, NULL);
    break;
  case 2:
    menu_cell_basic_draw(ctx, cell_layer, "Feeds", NULL, NULL);
    break;
  default:
    break;
  }
}

static int16_t get_cell_height_callback(struct MenuLayer *menu_layer,
                                        MenuIndex *cell_index, void *context) {
  const int16_t cell_height = 44;
  return cell_height;
}

static void select_callback(struct MenuLayer *menu_layer, MenuIndex *cell_index,
                            void *context) {
  // Do something in response to the button press
}

static void window_load(Window *window) {
  Layer *window_layer = window_get_root_layer(window);
  GRect bounds = layer_get_bounds(window_layer);

  s_menu_layer = menu_layer_create(bounds);
  menu_layer_set_click_config_onto_window(s_menu_layer, window);

  menu_layer_set_callbacks(s_menu_layer, NULL,
                           (MenuLayerCallbacks){
                               .get_num_rows = get_num_rows_callback,
                               .draw_row = draw_row_callback,
                               .get_cell_height = get_cell_height_callback,
                               .select_click = select_callback,

                           });
  layer_add_child(window_layer, menu_layer_get_layer(s_menu_layer));
}

static void window_unload(Window *window) {
  menu_layer_destroy(s_menu_layer);
  window_destroy(window);
}

void start_menu_push() {
  if (!s_window_start) {
    s_window_start = window_create();
    window_set_window_handlers(s_window_start, (WindowHandlers){
                                                   .load = window_load,
                                                   .unload = window_unload,
                                               });
  }
  window_stack_push(s_window_start, true);
}