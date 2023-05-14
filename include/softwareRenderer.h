#ifndef renderer_h
#define renderer_h

#include <SDL2/SDL.h>
#include <vec2.h>
#include <vec3.h>
#include <polygon.h>
#include <vector>

class softwareRenderer
{
public:
    softwareRenderer(int width, int height) : SCREEN_HEIGHT(height), SCREEN_WIDTH(width){};

private:
    int SCREEN_WIDTH;
    int SCREEN_HEIGHT;
    std::vector<uint32_t> pixels;

    int focalLenght = 50;

    SDL_Window *SDLwindow;
    SDL_Renderer *SDLrenderer;
    SDL_Texture *SDLtexture;

public:
    void init();
    void render();
    void resizeWindow();
    void end();
    void clearBuffer();
    void drawPolygon(polygon *polygon);
    void drawPolygons();
};
#endif