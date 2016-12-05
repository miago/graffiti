#ifndef DISPLAY_APP_H
#define DISPLAY_APP_H
#include <stdint.h>

#define ROW1 0
#define ROW2 8
#define ROW3 16

typedef enum
{
	DISPLAY_INIT = 0,
    DISPLAY_WRITE = 1,
    DISPLAY_CLEAR_ALL = 2,
    DISPLAY_CLEAR_ROW = 3,
    DISPLAY_RESET = 4,

	/* commands from the display module to other modules */
    DISPLAY_OK = 10,
    DISPLAY_ERROR = 11, /* when display has not been initialized */
    DISPLAY_UNIMPLEMENTED = 12
} displayMessageType_t;

typedef struct {
    displayMessageType_t message_type;
    uint8_t row_number;
    char* text;
} displayMessageFormat_t;

/* function prototypes */
displayMessageFormat_t* display_process_message(displayMessageFormat_t* display_message);

#endif
