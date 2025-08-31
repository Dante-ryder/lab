#include <game.h>
#include <iostream>
#include <Renderer.h>
#include <board.h>

using namespace std;

Board board;
extern Renderer renderer;
bool running = 0;
char lastTurn = 'n';
Game::Game() {}

void Game::start()
{
    cout << "Game started!" << endl;
    running = 1;

    while (running)
    {
        handleEvents();

        board.draw();
        renderer.delay(16);
    }
}

void Game::handleEvents()
{
    SDL_Event e;
    while (SDL_PollEvent(&e))
    {
        if (e.type == SDL_QUIT)
        {
            running = false;
        }
        else if (e.type == SDL_MOUSEBUTTONDOWN)
        {
            cout << "Mouse clicked at: " << e.button.x << ", " << e.button.y << endl;
            setXorO(e.button.x, e.button.y);
        }
    }
}

void Game::setXorO(int mx, int my)
{
    if (board.checkForWinner() != 'n' || board.checkForDraw())
    {
        board.reset();
        return;
    }

    int row = -1, col = -1;
    if (mx > 170 && mx < 270)
    {
        col = 1;
    }
    else if (mx > 270 && mx < 370)
    {
        col = 2;
    }
    else if (mx > 370 && mx < 470)
    {
        col = 3;
    }
    if (my > 90 && my < 190)
    {
        row = 1;
    }
    else if (my > 190 && my < 290)
    {
        row = 2;
    }
    else if (my > 290 && my < 390)
    {
        row = 3;
    }
    if (row != -1 && col != -1)
    {
        if (lastTurn == 'n' || lastTurn == 'O')
        {
            lastTurn = 'X';
            board.setXorO(lastTurn, row, col);
        }
        else if (lastTurn == 'X')
        {
            lastTurn = 'O';
            board.setXorO(lastTurn, row, col);
        }
    }

    board.printCurrentPosition();
}

void Game::greetWinner(char winner)
{
    cout << "Congratulations " << winner << endl;
}

void Game::announceDraw()
{
    cout << "Match Drawn: Tough Match Though" << endl;
}

Game::~Game() {
    renderer.~Renderer();
    board.~Board();
}