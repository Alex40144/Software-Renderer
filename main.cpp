
#include <SDL2/SDL.h>
#include <vec2.h>
 
int main()
{
    int width = 640;
    int height = 480;
 
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window *window = SDL_CreateWindow("Button Factory", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);

    SDL_Texture *screen_texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, width, height);

    SDL_SetWindowMinimumSize(window, 320, 240);


    bool open = true;
    while(open){
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                open = false;
            }
            if (event.type == SDL_WINDOWEVENT) {
                if (event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED) {
                    SDL_GetWindowSize(window, &width, &height);
                    SDL_RenderSetLogicalSize(renderer, width, height);

                }
            }
        }
        unsigned int *pixels = (unsigned int*)calloc(height * width * 4, 1);

        Vec2<int> rect[] = {{50, 50}, {250,250}};

        for (int y = 0; y < height; ++y) {
            for (int x = 0; x < width; ++x) {
                if (x > rect[0].GetX() && x < rect[1].GetX() && y > rect[0].GetY() && y < rect[1].GetY()){
                    pixels[x + y * width] = 0x00ffff55;
                }
            }
        }

        SDL_RenderClear(renderer);
        SDL_UpdateTexture(screen_texture, NULL, pixels, width * 4);
        SDL_RenderCopy(renderer, screen_texture, NULL, NULL);
        SDL_RenderPresent(renderer);
        free(pixels);
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}