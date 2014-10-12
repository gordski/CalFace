#include <pebble.h>

Window *window;

TextLayer *events_layer;

InverterLayer *inverter_layer;

char events[255];

void render() 
{
  text_layer_set_text(events_layer, events);
  text_layer_set_font(events_layer, fonts_get_system_font(FONT_KEY_GOTHIC_18));
	text_layer_set_text_alignment(events_layer, GTextAlignmentLeft);
}

void in_received_handler(DictionaryIterator *received, void *context)
{
	Tuple *tuple;
	
  int i = 0;
  
  while((tuple = dict_find(received, i)))
  {
    snprintf(events, 255, "%s", tuple->value->cstring);
    //APP_LOG(APP_LOG_LEVEL_INFO, "Received Status: %s", tuple->value->cstring);
    i++;
	}
  
  render();
}

 void in_dropped_handler(AppMessageResult reason, void *context) 
 {
  snprintf(events, 255, "BUGGER %d", reason);
  render();
 }

void init(void) 
{
  APP_LOG(APP_LOG_LEVEL_INFO, "Start!");

  window = window_create();
	window_stack_push(window, true);
	
	app_message_register_inbox_received(in_received_handler);
  app_message_register_inbox_dropped(in_dropped_handler);
		
	app_message_open(app_message_inbox_size_maximum(), 0);
  
  events_layer = text_layer_create(GRect(0, 10, 144, 168));
  text_layer_set_background_color(events_layer, GColorClear);
  layer_add_child(window_get_root_layer(window), text_layer_get_layer(events_layer));
  
  inverter_layer = inverter_layer_create(GRect(0, 0, 144, 168));
	layer_add_child(window_get_root_layer(window), inverter_layer_get_layer(inverter_layer));
  
  snprintf(events, 255, "%s", "BADDD!");
  
  render();
}

void deinit(void) 
{
	app_message_deregister_callbacks();
  text_layer_destroy(events_layer);
	window_destroy(window);
}

int main( void ) 
{
	init();
	app_event_loop();
	deinit();
}