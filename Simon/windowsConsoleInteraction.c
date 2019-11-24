#include "windowsConsoleInteraction.h"

HANDLE hStdin;
DWORD fdwSaveOldMode;
EVENT retEvent;

VOID ErrorExit(LPSTR);
VOID KeyEventProc(KEY_EVENT_RECORD);
VOID MouseEventProc(MOUSE_EVENT_RECORD);
VOID ResizeEventProc(WINDOW_BUFFER_SIZE_RECORD);

EVENT eventMain(VOID)
{
		DWORD cNumRead, fdwMode, i;
	INPUT_RECORD irInBuf[128];
	int counter = 0;

	// Get the standard input handle.

	hStdin = GetStdHandle(STD_INPUT_HANDLE);
	if (hStdin == INVALID_HANDLE_VALUE)
		ErrorExit("GetStdHandle");

	// Save the current input mode, to be restored on exit.

	if (!GetConsoleMode(hStdin, &fdwSaveOldMode))
		ErrorExit("GetConsoleMode");

	// Enable the window and mouse input events.

	fdwMode = ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT;
	fdwMode &= ~ENABLE_QUICK_EDIT_MODE;
	SetConsoleMode(hStdin, fdwMode | ENABLE_EXTENDED_FLAGS);
	if (!SetConsoleMode(hStdin, fdwMode))
		ErrorExit("SetConsoleMode");

	// Wait for the events.

	if (!ReadConsoleInput(
		hStdin,      // input buffer handle
		irInBuf,     // buffer to read into
		128,         // size of read buffer
		&cNumRead)) // number of records read
		ErrorExit("ReadConsoleInput");

	// Dispatch the events to the appropriate handler.

	i = 0;
	switch (irInBuf[i].EventType)
	{
	case KEY_EVENT: // keyboard input
		KeyEventProc(irInBuf[i].Event.KeyEvent);
		break;

	case MOUSE_EVENT: // mouse input
		MouseEventProc(irInBuf[i].Event.MouseEvent);
		break;

	case WINDOW_BUFFER_SIZE_EVENT: // scrn buf. resizing
		ResizeEventProc(irInBuf[i].Event.WindowBufferSizeEvent);
		break;

	case FOCUS_EVENT:  // disregard focus events

	case MENU_EVENT:   // disregard menu events
		break;

	default:
		ErrorExit("Unknown event type");
		break;
	}

	// Restore input mode on exit.

	SetConsoleMode(hStdin, fdwSaveOldMode);

	return retEvent;
}

VOID ErrorExit(LPSTR lpszMessage)
{
	fprintf(stderr, "%s\n", lpszMessage);

	// Restore input mode on exit.

	SetConsoleMode(hStdin, fdwSaveOldMode);

	ExitProcess(0);
}

VOID KeyEventProc(KEY_EVENT_RECORD ker)
{
	/*printf("Key event: ");
	if (ker.bKeyDown)
		printf("key pressed\n");
	else printf("key released\n");*/

	retEvent.regEvent = _KEY_EVENT;
	retEvent.event.keyPressed = ker.bKeyDown;
	retEvent.event.keyPressed = ker.uChar.AsciiChar;
}
VOID MouseEventProc(MOUSE_EVENT_RECORD mer)
{
#ifndef MOUSE_HWHEELED
#define MOUSE_HWHEELED 0x0008
#endif
	//printf("Mouse event: ");

	switch (mer.dwEventFlags)
	{
	case 0:
		retEvent.regEvent = _MOUSE_EVENT;
		if (mer.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
		{
			//printf("left button press \n");
			retEvent.event.mouseEvent = mer.dwButtonState;
			retEvent.event.mouseCoord = mer.dwMousePosition;
		}
		else if (mer.dwButtonState == RIGHTMOST_BUTTON_PRESSED)
		{
			//printf("right button press \n");
			retEvent.event.mouseEvent = mer.dwButtonState;
		}
		else
		{
			//printf("button press\n");
			retEvent.event.mouseEvent = mer.dwButtonState;
		}
		break;
	case DOUBLE_CLICK:
		//printf("double click\n");
		retEvent.event.mouseEvent = mer.dwButtonState;
		break;
	case MOUSE_HWHEELED:
		//printf("horizontal mouse wheel\n");
		retEvent.event.mouseEvent = mer.dwButtonState;
		break;
	case MOUSE_MOVED:
		//printf("mouse moved\n");
		retEvent.event.mouseEvent = mer.dwButtonState;
		break;
	case MOUSE_WHEELED:
		//printf("vertical mouse wheel\n");
		retEvent.event.mouseEvent = mer.dwButtonState;
		break;
	default:
		//printf("unknown\n");
		retEvent.event.mouseEvent = mer.dwButtonState;
		break;
	}
}
VOID ResizeEventProc(WINDOW_BUFFER_SIZE_RECORD wbsr)
{
	//printf("Resize event\n");
	//printf("Console screen buffer is %d columns by %d rows.\n", wbsr.dwSize.X, wbsr.dwSize.Y);
}