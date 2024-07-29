#include<time.h>
#include"include/Chitra.h"
#define WIDTH 1900
#define HEIGHT 1000


static uint32_t pixels[WIDTH*HEIGHT];
void Setup(Chitra chitra);
void EventLoop(Chitra chitra,clock_t);