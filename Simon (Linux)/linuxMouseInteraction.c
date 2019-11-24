#include <cstdio>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <linux/input.h>
#include <fcntl.h>
#include <X11/Xlib.h>

#define MOUSEFILE "/dev/input/event4"

int main()
{
	int fd;
	struct input_event ie;
	Display* dpy;
	Window root, child;
	int rootX, rootY, winX, winY;
	unsigned int mask;

	dpy = XOpenDisplay(NULL);
	XQueryPointer(dpy, DefaultRootWindow(dpy), &root, &child,
		&rootX, &rootY, &winX, &winY, &mask);

	if ((fd = open(MOUSEFILE, O_RDONLY)) == -1) {
		perror("opening device");
		exit(EXIT_FAILURE);
	}

	while (read(fd, &ie, sizeof(struct input_event))) {
		if (ie.type == 2) {
			if (ie.code == 0) {
				XQueryPointer(dpy, DefaultRootWindow(dpy), &root, &child,
					&rootX, &rootY, &winX, &winY, &mask);
				//rootX += ie.value;
			}
			else if (ie.code == 1) {
				XQueryPointer(dpy, DefaultRootWindow(dpy), &root, &child,
					&rootX, &rootY, &winX, &winY, &mask);
				// rootY += ie.value;
			}
			printf("time%ld.%06ld\tx %d\ty %d\n",
				ie.time.tv_sec, ie.time.tv_usec, rootX, rootY);
		}
		else
			printf("time %ld.%06ld\ttype %d\tcode %d\tvalue %d\n",
				ie.time.tv_sec, ie.time.tv_usec, ie.type, ie.code, ie.value);
	}
	return 0;
}