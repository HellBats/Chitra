#include"include/WindowAPI/Window.h"
#include"include/UpperLayer.h"


void main(void) {
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    SDL_Texture *texture;
    SDL_Init(SDL_INIT_EVERYTHING);
    Chitra chitra;

    chitra.pixels = pixels;
    chitra.width = WIDTH;
    chitra.height = HEIGHT;
    chitra.stride = chitra.width;
    ChitraFill(chitra,0xFFFFFFFF);

    SDL_CreateWindowAndRenderer(chitra.width,chitra.height,0,&window,&renderer);
    texture = SDL_CreateTexture(renderer,SDL_PIXELFORMAT_ARGB8888,SDL_TEXTUREACCESS_STREAMING,
        chitra.width,chitra.height);
    Setup(chitra);
    clock_t start = clock();
    int fps = 0;
    while (1) {
        if((clock()-start)/CLOCKS_PER_SEC<1)
        {
            fps++;
        }
        if((clock()-start)/CLOCKS_PER_SEC>3)
        {
            printf("\r%d",fps);
            break;
        }
        EventLoop(chitra,start);
        SDL_UpdateTexture(texture,NULL,chitra.pixels,chitra.width*sizeof(uint32_t));
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer,texture,NULL,NULL);
        SDL_RenderPresent(renderer);
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}