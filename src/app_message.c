#include <pebble.h>
#include "main_window.h"

static int event_count = 0;

static void (*func_lookup[][2])(const char *val) =
{
  {set_time_bracket, set_event_title},
  {set_later_event_1_time, set_later_event_1_title},
  {set_later_event_2_time, set_later_event_2_title}
};
  
void in_received_handler(DictionaryIterator *received, void *context)
{
	Tuple *tuple;
  int i;
  
  APP_LOG(APP_LOG_LEVEL_INFO, "Message received!");
  
  tuple = dict_read_first(received);
  
  for(i = 0; i < 2 && tuple; i++)
  {
    func_lookup[event_count][tuple->key](tuple->value->cstring);
    APP_LOG(APP_LOG_LEVEL_INFO, "%s: %s", tuple->key == 0 ? "Time" : "Title", tuple->value->cstring);
    tuple = dict_read_next(received);
	}
 
  event_count++;
}

void in_dropped_handler(AppMessageResult reason, void *context) 
{
  APP_LOG(APP_LOG_LEVEL_INFO, "Message dropped!");
}

void out_sent_handler(DictionaryIterator *sent, void *context) 
{
  APP_LOG(APP_LOG_LEVEL_INFO, "Acked!");
}


void out_failed_handler(DictionaryIterator *failed, AppMessageResult reason, void *context) 
{
  APP_LOG(APP_LOG_LEVEL_INFO, "Nacked!");
}

void init(void) 
{
  APP_LOG(APP_LOG_LEVEL_INFO, "Start!");

	app_message_register_inbox_received(in_received_handler);
  app_message_register_inbox_dropped(in_dropped_handler);
  app_message_register_outbox_sent(out_sent_handler);
  app_message_register_outbox_failed(out_failed_handler);
  	
	app_message_open(app_message_inbox_size_maximum(), app_message_outbox_size_maximum());
  
  DictionaryIterator *iter;
  app_message_outbox_begin(&iter);
  
  Tuplet value = TupletInteger(1, 42);
  dict_write_tuplet(iter, &value);
  
  app_message_outbox_send();
  
  show_main_window();
}

void deinit(void) 
{
	app_message_deregister_callbacks();
  hide_main_window();
}

int main( void ) 
{
	init();
	app_event_loop();
	deinit();
}