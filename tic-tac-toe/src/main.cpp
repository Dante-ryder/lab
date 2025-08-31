#include <iostream>
#include <game.h>

using namespace std;

int main()
{
    cout << "hello world!" << endl;
    Game game;
    game.start();
    game.~Game();
    return 0;
}