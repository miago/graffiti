
#include <stdint.h>
#include "display_app.h"
#include "display.h"

/**
* @brief Flag containing the initialisation state of the display module 
* 0 when uninitialized, 1 when initialized 
**/
uint8_t display_initialized = 0;


/**
* @brief Processes a message
**/
displayMessageFormat_t* display_process_message(displayMessageFormat_t* display_message){
    if((display_message->message_type != DISPLAY_INIT) && (display_initialized == 0)){
        display_message->message_type = DISPLAY_ERROR;
        return display_message;
    }

	switch(display_message->message_type){
		case DISPLAY_INIT:
			display_init();
			display_initialized = 1;
			display_message->message_type = DISPLAY_OK;
			return display_message;
		case DISPLAY_RESET:
			glcd_reset(); 	
			display_message->message_type = DISPLAY_OK;
			return display_message;
		case DISPLAY_WRITE:
			display_write_row(display_message->row_number, display_message->text);
			display_message->message_type = DISPLAY_OK;
			return display_message;
		case DISPLAY_CLEAR_ROW:
			display_clear_row(display_message->row_number);
			display_message->message_type = DISPLAY_OK;
			return display_message;		
		default:
			display_message->message_type = DISPLAY_UNIMPLEMENTED;
			return display_message;
	}
}
