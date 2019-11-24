#ifndef WINDOWS_CONSOLE_INTERACTION
#define WINDOWS_CONSOLE_INTERACTION

#include <windows.h>
#include <stdio.h>

typedef enum event {
	_MOUSE_EVENT = 0,
	_KEY_EVENT
}eventType;

typedef struct Interaction_Event_t {
	eventType regEvent;
	union eventContent {
		struct keyPress {
			BOOL keyDown;
			char keyPressed;
		};
		struct mouse {
			int mouseEvent;
			COORD mouseCoord;
		};
	}event;
}EVENT;

EVENT eventMain(VOID);

#endif // !WINDOWS_CONSOLE_INTERACTION
