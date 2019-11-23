#ifndef LINUX_MOUSE_INTERACTION
#define LINUX_MOUSE_INTERACTION

typedef struct _COORD {
	short X;
	short Y;
} COORD;

typedef enum event {
	_MOUSE_EVENT = 0,
	_OTHER_EVENT
}eventType;

typedef struct Interaction_Event_t {
	eventType regEvent;
	union eventContent {
		char keyPress;
		struct mouse {
			int mouseEvent;
			COORD mouseCoord;
		};
	}event;
}EVENT;




#endif // !LINUX_MOUSE_INTERACTION
