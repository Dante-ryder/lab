#ifndef GAME_H
#define GAME_H

class Game
{
private:
    bool running = 0;
    char lastTurn = 'n';

public:
    Game();
    void start();
    void handleEvents();
    void setXorO(int mx, int my);
    void greetWinner(char winner);
    void announceDraw();
    ~Game();
};

#endif