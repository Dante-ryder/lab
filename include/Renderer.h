#ifndef RENDERER_H
#define RENDERER_H

#include <SDL.h>
#include <string>

using namespace std;

enum class GameEventType
{
    CELL_CLICKED,
    RESET_REQUESTED,
    QUIT_REQUESTED
};

class Renderer
{
private:
    SDL_Renderer *renderer;
    SDL_Window *window;
    SDL_Event e;
    static const int WINDOW_WIDTH = 640;
    static const int WINDOW_HEIGHT = 480;
    string title;
    Uint8 r = 255;
    Uint8 g = 255;
    Uint8 b = 255;
    Uint8 a = 255;

    bool initialized = false;

public:
    explicit Renderer(const string &title);

    Renderer(const Renderer &) = delete;
    Renderer &operator=(const Renderer &) = delete;

    void drawGrid(Uint16 r, Uint16 c, Uint16 x, Uint16 y, Uint16 h, Uint16 w);
    void drawLine(Uint16 x1, Uint16 y1, Uint16 x2, Uint16 y2);
    void drawPoint(Uint16 px, Uint16 py);
    void setColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a);
    void clear();
    void present();
    void delay(Uint32 ms) const;
    void delay() const;

    ~Renderer();
};

#endif