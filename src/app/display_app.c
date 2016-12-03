
#include <stdint.h>
#include "display_app.h"
#include "display.h"

uint8_t display_initialized = 0;

displayMessageFormat_t* display_process_message(displayMessageFormat_t* display_message){

	switch(display_message->message_type){
		case DISPLAY_INIT:
			/*display_init();
			*/
		break;
	}
}
