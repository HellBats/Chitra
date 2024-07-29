#include"include/WindowAPI/Window.h"
#include"include/UpperLayer.h"


void main(void) {
    Display *dpy;
    Window win;
    int scr;
    Chitra chitra;
    XImage *img;


    chitra.pixels = pixels;
    chitra.width = WIDTH;
    chitra.height = HEIGHT;
    chitra.stride = chitra.width;
    ChitraFill(chitra,0xFFFFFFFF);
    dpy = XOpenDisplay(NULL);
    if (dpy == NULL) {
        fprintf(stderr, "Cannot open display\n");
        exit(1);
    }

    scr = DefaultScreen(dpy);
    win = XCreateSimpleWindow(dpy, RootWindow(dpy, scr), 0, 0, chitra.width, chitra.height, 1,
                              BlackPixel(dpy, scr), WhitePixel(dpy, scr));

    XSelectInput(dpy, win, ExposureMask | KeyPressMask);
    XMapWindow(dpy, win);
    ChitraFill(chitra,0xFFFFFFFF);
    // pthread_create(&id,NULL,KeyPressEvent_,(void *)&args);
    // pthread_join(id,NULL);
    Setup(chitra);
    clock_t start = clock();
    while (1) {
        // XNextEvent(dpy, &e);
        EventLoop(chitra,start);
        // if (args->event.type == KeyPress)
        //     break;
        //     // XNextEvent(dpy, &e);
        
        img = XCreateImage(dpy, DefaultVisual(dpy, scr), DefaultDepth(dpy, scr),
                    ZPixmap, 0, (char *)chitra.pixels, chitra.width, chitra.height, 32, 0);
        if (img == NULL) {
            fprintf(stderr, "Failed to create XImage\n");
            exit(1);
        }
    // Draw the image to the window
        XPutImage(dpy, win, DefaultGC(dpy, scr), img, 0, 0, 0, 0, chitra.width, chitra.height);
        // free(img);
        // XDestroyImage(img);
    }

    XDestroyWindow(dpy, win);
    XCloseDisplay(dpy);
}