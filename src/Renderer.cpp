#include <iostream>
#include <Renderer.h>
#include <Error.h>
#include <board.h>

using namespace std;

Error error;

Renderer::Renderer(const string &title) : title(title)
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        error.throw_error("SDL could not initialize! SDL_Error: " + string(SDL_GetError()));
        return;
    }

    window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);

    if (!window)
    {
        error.throw_error("Window could not be created! SDL_Error: " + string(SDL_GetError()));
        SDL_Quit();
        return;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if (!renderer)
    {
        error.throw_error("Renderer could not be created! SDL_Error: " + string(SDL_GetError()));
        SDL_DestroyWindow(window);
        SDL_Quit();
        return;
    }
    cout << "Renderer Initialized SuccessFully!" << endl;
}

void Renderer::delay(Uint32 ms) const
{
    SDL_Delay(ms);
}

void Renderer::delay() const
{
    SDL_Delay(20);
}

void Renderer::setColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
    SDL_SetRenderDrawColor(renderer, r, g, b, a);
}

void Renderer::drawGrid(Uint16 r, Uint16 c, Uint16 x, Uint16 y, Uint16 h, Uint16 w)
{
    SDL_Rect rect = {x, y, h * r, w * c};

    SDL_RenderFillRect(renderer, &rect);

    setColor(96, 96, 96, 255);

    Uint16 x1, y1, x2, y2 = 0;

    for (Uint16 i = 1; i <= r; i++)
    {
        x1 = x;
        y1 = (h * i) + y;
        y2 = y1;
        x2 = (w * c) + x;
        drawLine(x1, y1, x2, y2);
    }

    for (Uint16 j = 1; j <= c; j++)
    {
        x1 = (w * j) + x;
        y1 = y;
        y2 = (h * r) + y;
        x2 = x1;
        drawLine(x1, y1, x2, y2);
    }
}

void Renderer::drawLine(Uint16 x1, Uint16 y1, Uint16 x2, Uint16 y2)
{
    SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
}

void Renderer::drawPoint(Uint16 px, Uint16 py)
{
    SDL_RenderDrawPoint(renderer, px, py);
}

void Renderer::clear()
{
    SDL_RenderClear(renderer);
}

void Renderer::present()
{
    SDL_RenderPresent(renderer);
}

Renderer::~Renderer()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_StopTextInput();

    SDL_Quit();
}