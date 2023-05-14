#include <softwareRenderer.h>

void softwareRenderer::init()
{
    SDL_Init(SDL_INIT_VIDEO);

    SDLwindow = SDL_CreateWindow("Software Renderer", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_ALLOW_HIGHDPI | SDL_WINDOW_RESIZABLE);

    SDLrenderer = SDL_CreateRenderer(SDLwindow, -1, SDL_RENDERER_PRESENTVSYNC);

    SDLtexture = SDL_CreateTexture(SDLrenderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, SCREEN_WIDTH, SCREEN_HEIGHT);

    pixels.resize(SCREEN_HEIGHT * SCREEN_WIDTH);
}

void softwareRenderer::render()
{
    SDL_UpdateTexture(SDLtexture, NULL, &pixels[0], SCREEN_WIDTH * 4);
    SDL_RenderCopy(SDLrenderer, SDLtexture, NULL, NULL);
    SDL_RenderPresent(SDLrenderer);
}

void softwareRenderer::drawPolygon(polygon *polygon)
{
    for (int i = 0; i < size(polygon->getPointTable()); i++)
    {
        int x = polygon->getPointTable().at(i).X;
        int y = polygon->getPointTable().at(i).Y;
        pixels[x + y * SCREEN_WIDTH] = 0xff0000ff;
    }

    for (int i = 0; i < size(polygon->getEdgeTable()); i++)
    {
        std::vector<int> points = polygon->getEdgeTable().at(i);
        int x1 = polygon->getPointTable().at(points.at(0)).X;
        int y1 = polygon->getPointTable().at(points.at(0)).Y;
        int x2 = polygon->getPointTable().at(points.at(1)).X;
        int y2 = polygon->getPointTable().at(points.at(1)).Y;
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
}

void softwareRenderer::end()
{
    SDL_DestroyTexture(SDLtexture);
    SDL_DestroyRenderer(SDLrenderer);
    SDL_DestroyWindow(SDLwindow);
    SDL_Quit();
}

void softwareRenderer::resizeWindow()
{
    SDL_GetWindowSize(SDLwindow, &SCREEN_WIDTH, &SCREEN_HEIGHT);
    SDLtexture = SDL_CreateTexture(SDLrenderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, SCREEN_WIDTH, SCREEN_HEIGHT);
    pixels.resize(SCREEN_HEIGHT * SCREEN_WIDTH);
}

void softwareRenderer::clearBuffer()
{
    std::fill(pixels.begin(), pixels.end(), 0);
}