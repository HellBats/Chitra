#include<png.h>
#include"include/Chitra.h"


Chitra ReadPNG(char path[],int *height,int *width,int *channels);

Chitra WritePNG(char path[],Chitra chitra);