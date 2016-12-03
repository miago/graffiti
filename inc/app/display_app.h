#ifndef DISPLAY_APP_H
#define DISPLAY_APP_H
#include <stdint.h>

typedef enum
{
	DISPLAY_INIT = 0,
    DISPLAY_WRITE = 1,
    DISPLAY_CLEAR_ALL = 2,
    DISPLAY_CLEAR_ROW = 3,

	/* commands from the display module to other modules */
    DISPLAY_OK = 10,
    DISPLAY_ERROR = 11, /* when display has not been initialized */
} displayMessageType_t;

typedef struct {
    displayMessageType_t message_type;
    uint8_t row_number;
    /*uint8_t text[19];*/
} displayMessageFormat_t;

/* function prototypes */
displayMessageFormat_t* display_process_message(displayMessageFormat_t* display_message);

#endif