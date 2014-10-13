#include <pebble.h>
#include "main_window.h"

void in_received_handler(DictionaryIterator *received, void *context)
{
	Tuple *tuple;
  APP_LOG(APP_LOG_LEVEL_INFO, "Message received!");
  if((tuple = dict_read_first(received)))
  {
    set_time_bracket(tuple->value->cstring);
	}
  
  if((tuple = dict_read_next(received)))
  {
    set_event_title(tuple->value->cstring);
	}  
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