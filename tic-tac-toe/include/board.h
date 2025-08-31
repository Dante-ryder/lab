#ifndef BOARD_H
#define BOARD_H

#include <vector>

class Board
{
private:
    std::vector<std::vector<char>> grid;

    static const int SIZE = 3;

    static const int BOARD_X = 170;
    static const int BOARD_Y = 90;
    static const int BOARD_SIZE = 300;
    static const int CELL_SIZE = 100;

public:
    Board();
    void draw();
    void drawXrO(int row, int col, char type);
    void setXorO(char type, Uint16 r, Uint16 c);
    void printCurrentPosition() const;
    void reset();
    char checkForWinner() const;
    bool checkForDraw() const;
    ~Board();
};

#endif