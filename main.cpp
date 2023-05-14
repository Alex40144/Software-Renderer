#include <SDL2/SDL.h>
#include <vec2.h>
#include <vec3.h>
#include <polygon.h>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

int main()
{

    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window *window = SDL_CreateWindow("Software Renderer", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_ALLOW_HIGHDPI);

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);

    SDL_Texture *texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, SCREEN_WIDTH, SCREEN_HEIGHT);

    SDL_SetWindowMinimumSize(window, 320, 240);

    uint32_t pixels[SCREEN_HEIGHT * SCREEN_WIDTH];
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
        }

        polygon *line1 = new polygon();
        line1->addPoint(Vec3<int>{150, 150, 0});
        line1->addPoint(Vec3<int>{550, 300, 0});
        line1->addEdge(Vec3<int>{150, 150, 0}, Vec3<int>{550, 300, 0});

        for (int i = 0; i < size(line1->getPointTable()); i++)
        {
            int x = line1->getPointTable().at(i).X;
            int y = line1->getPointTable().at(i).Y;
            pixels[x + y * SCREEN_WIDTH] = 0xff0000ff;
        }

        for (int i = 0; i < size(line1->getEdgeTable()); i++)
        {
            std::vector<int> points = line1->getEdgeTable().at(i);
            int x1 = line1->getPointTable().at(points.at(0)).X;
            int y1 = line1->getPointTable().at(points.at(0)).Y;
            int x2 = line1->getPointTable().at(points.at(1)).X;
            int y2 = line1->getPointTable().at(points.at(1)).Y;
            int x = x1;
            int y = y1;
            int dx = abs(x2 - x1);
            int sx = x1 < x2 ? 1 : -1;
            int dy = -abs(y2 - y1);
            int sy = y1 < y2 ? 1 : -1;
            int error = dx + dy;

            while (1)
            {
                pixels[x1 + y1 * SCREEN_WIDTH] = 0xff0000ff;
                if (x1 == x2 && y1 == y2)
                    break;
                int e2 = 2 * error;
                if (e2 >= dy)
                {
                }
                if (x1 == x2)
                    break;
                error = error + dy;
                x1 = x1 + sx;
                if (e2 <= dx)
                {
                    if (y1 == y2)
                        break;
                    error = error + dx;
                    y1 = y1 + sy;
                }
            }
        }

        SDL_UpdateTexture(texture, NULL, pixels, SCREEN_WIDTH * 4);
        SDL_RenderCopy(renderer, texture, NULL, NULL);
        SDL_RenderPresent(renderer);
    }
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}