#ifndef WINDOWS_CONSOLE_INTERACTION
#define WINDOWS_CONSOLE_INTERACTION

#include <windows.h>
#include <stdio.h>

// stores a mouse or key eventy
typedef enum event {
	_MOUSE_EVENT = 0,
	_KEY_EVENT
}eventType;

// store an (almost) a entire envent
typedef struct Interaction_Event_t {
	eventType regEvent; // type of the event
	union eventContent {
		struct keyPress {
			BOOL keyDown;
			char keyPressed;
		}; // hold a key press or a mouse event
		struct mouse {
			int mouseEvent;
			COORD mouseCoord;
		};
	}event;
}EVENT;

// as this code was get from the stack overflow
// there was a main
// this was changed to eventMain
// and some functions are also changed
EVENT eventMain(VOID);

#endif // WINDOWS_CONSOLE_INTERACTION
