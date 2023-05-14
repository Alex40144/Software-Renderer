#include <SDL2/SDL.h>
#include <vec2.h>
#include <vec3.h>
#include <polygon.h>
#include <softwareRenderer.h>

int SCREEN_WIDTH = 960;
int SCREEN_HEIGHT = 540;

int main()
{

    softwareRenderer *renderer1 = new softwareRenderer(960, 540);

    renderer1->init();

    bool open = true;
    while (open)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                open = false;
            }
            if (event.type == SDL_WINDOWEVENT)
            {
                if (event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
                {
                    renderer1->resizeWindow();
                }
            }
        }

        polygon *line1 = new polygon();
        line1->addPoint(Vec3<int>{150, 150, 0});
        line1->addPoint(Vec3<int>{50, 200, 0});
        line1->addEdge(Vec3<int>{150, 150, 0}, Vec3<int>{50, 200, 0});

        renderer1->drawPolygon(line1);

        renderer1->render();
        renderer1->clearBuffer();
    }
    renderer1->end();
    return 0;
}