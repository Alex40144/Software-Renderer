#include <SDL2/SDL.h>
#include <vec2.h>
#include <vec3.h>
#include <polygon.h>
#include <softwareRenderer.h>

int SCREEN_WIDTH = 960;
int SCREEN_HEIGHT = 540;

uint32_t now = SDL_GetPerformanceCounter();
uint32_t last = 0;
double deltatime = 0;

int main()
{

    softwareRenderer *renderer = new softwareRenderer(960, 540);

    renderer->init();

    polygon *cube = new polygon();
    // ABCD front face. clockwise from top left. EFGH back face clockwise from top left
    cube->addPoint(Vec3<int>{250, 250, 250});    // A
    cube->addPoint(Vec3<int>{250, -250, 250});   // B
    cube->addPoint(Vec3<int>{-250, -250, 250});  // C
    cube->addPoint(Vec3<int>{-250, 250, 250});   // D
    cube->addPoint(Vec3<int>{250, 250, -250});   // E
    cube->addPoint(Vec3<int>{250, -250, -250});  // F
    cube->addPoint(Vec3<int>{-250, -250, -250}); // G
    cube->addPoint(Vec3<int>{-250, 250, -250});  // H

    cube->addEdge(Vec3<int>{250, 250, 250}, Vec3<int>{250, -250, 250});     // AB
    cube->addEdge(Vec3<int>{250, -250, 250}, Vec3<int>{-250, -250, 250});   // BC
    cube->addEdge(Vec3<int>{-250, -250, 250}, Vec3<int>{-250, 250, 250});   // CD
    cube->addEdge(Vec3<int>{-250, 250, 250}, Vec3<int>{250, 250, 250});     // DA
    cube->addEdge(Vec3<int>{250, 250, -250}, Vec3<int>{250, -250, -250});   // EF
    cube->addEdge(Vec3<int>{250, -250, -250}, Vec3<int>{-250, -250, -250}); // FG
    cube->addEdge(Vec3<int>{-250, -250, -250}, Vec3<int>{-250, 250, -250}); // GH
    cube->addEdge(Vec3<int>{-250, 250, -250}, Vec3<int>{250, 250, -250});   // HE
    cube->addEdge(Vec3<int>{250, 250, 250}, Vec3<int>{250, 250, -250});     // AE
    cube->addEdge(Vec3<int>{250, -250, 250}, Vec3<int>{250, -250, -250});   // BF
    cube->addEdge(Vec3<int>{-250, -250, 250}, Vec3<int>{-250, -250, -250}); // CG
    cube->addEdge(Vec3<int>{-250, 250, 250}, Vec3<int>{-250, 250, -250});   // DH

    bool open = true;
    while (open)
    {
        last = now;
        now = SDL_GetPerformanceCounter();
        deltatime = (float)((now - last) * 1000 / (float)SDL_GetPerformanceFrequency());
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
                    renderer->resizeWindow();
                }
            }
        }

        cube->setRotation({cube->getRotation().X + (0.001 * deltatime), cube->getRotation().Y + (0.001 * deltatime), cube->getRotation().Z});
        printf("%f\n", cube->getRotation().Y);
        renderer->drawPolygon(cube);

        renderer->render();
        renderer->clearBuffer();
    }
    renderer->end();
    return 0;
}