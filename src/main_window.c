#include "main_window.h"
#include <pebble.h>

// BEGIN AUTO-GENERATED UI CODE; DO NOT MODIFY
static Window *s_window;
static GFont s_res_gothic_28_bold;
static GFont s_res_gothic_18_bold;
static TextLayer *time_bracket;
static TextLayer *event_title;

static char time_str[14];
static char title_str[100];

static void initialise_ui(void) {
  s_window = window_create();
  window_set_background_color(s_window, GColorBlack);
  window_set_fullscreen(s_window, false);
  
  s_res_gothic_28_bold = fonts_get_system_font(FONT_KEY_GOTHIC_28_BOLD);
  s_res_gothic_18_bold = fonts_get_system_font(FONT_KEY_GOTHIC_18_BOLD);
  // time_bracket
  time_bracket = text_layer_create(GRect(0, 0, 144, 31));
  text_layer_set_text(time_bracket, "Loading...");
  text_layer_set_text_alignment(time_bracket, GTextAlignmentCenter);
  text_layer_set_font(time_bracket, s_res_gothic_28_bold);
  layer_add_child(window_get_root_layer(s_window), (Layer *)time_bracket);
  
  // event_title
  event_title = text_layer_create(GRect(0, 30, 144, 122));
  text_layer_set_background_color(event_title, GColorClear);
  text_layer_set_text_color(event_title, GColorWhite);
  text_layer_set_text(event_title, "");
  text_layer_set_text_alignment(event_title, GTextAlignmentCenter);
  text_layer_set_font(event_title, s_res_gothic_18_bold);
  layer_add_child(window_get_root_layer(s_window), (Layer *)event_title);
}

static void destroy_ui(void) {
  window_destroy(s_window);
  text_layer_destroy(time_bracket);
  text_layer_destroy(event_title);
}
// END AUTO-GENERATED UI CODE

static void handle_window_unload(Window* window) {
  destroy_ui();
}

void show_main_window(void) {
  initialise_ui();
  window_set_window_handlers(s_window, (WindowHandlers) {
    .unload = handle_window_unload,
  });
  window_stack_push(s_window, true);
}

void hide_main_window(void) {
  window_stack_remove(s_window, true);
}

void set_time_bracket(const char *time)
{
  snprintf(time_str, sizeof(time_str), "%s", time);
  text_layer_set_text(time_bracket, time_str);
}

void set_event_title(const char *title)
{
  snprintf(title_str, sizeof(title_str), "%s", title);
  text_layer_set_text(event_title, title_str);
}
