
#include <SDL.h>
 
int main(int argc, char *argv[])
{
 
    // returns zero on success else non-zero
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        printf("error initializing SDL: %s\n", SDL_GetError());
    }
    SDL_Window* win = SDL_CreateWindow("Button Factory",
                                       SDL_WINDOWPOS_CENTERED,
                                       SDL_WINDOWPOS_CENTERED,
                                       1000, 1000, 0);
    SDL_Event event;
    
    while(!(event.type == SDL_QUIT)){
        SDL_Delay(10);  // setting some Delay
        SDL_PollEvent(&event);  // Catching the poll event.
    }
    return 0;
}