#include <iostream>
#include <vector>
#include <Renderer.h>
#include <board.h>

using namespace std;

Renderer renderer("Tic Tac Toe");

Board::Board()
{
    grid.resize(SIZE, vector<char>(SIZE, 'n'));
}

void Board::draw()
{
    renderer.setColor(255, 255, 255, 255);
    renderer.clear();

    renderer.setColor(200, 200, 200, 255);
    renderer.drawGrid(3, 3, BOARD_X, BOARD_Y, 100, 100);

    for (int r = 0; r < 3; r++)
    {
        for (int c = 0; c < 3; c++)
        {
            if (grid[r][c] != 'n')
            {
                drawXrO(r, c, grid[r][c]);
            }
        }
    }

    renderer.present();
    renderer.delay(16);
}

void Board::drawXrO(int row, int col, char type)
{
    int x = BOARD_X + col* CELL_SIZE;
    int y = BOARD_Y + row * CELL_SIZE;

    renderer.setColor(255, 0, 0, 255);

    if (type == 'X')
    {
        // Draw X
        renderer.drawLine(x + 20, y + 20, x + 80, y + 80);
        renderer.drawLine(x + 80, y + 20, x + 20, y + 80);
    }
    else if (type == 'O')
    {
        // Draw O (circle)
        int cx = x + CELL_SIZE / 2;
        int cy = y + CELL_SIZE / 2;
        int radius = 30;

        for (double angle = 0; angle < 2 * M_PI; angle += 0.01)
        {
            int px = (int)(cx + radius * cos(angle));
            int py = (int)(cy + radius * sin(angle));
            renderer.drawPoint(px, py);
        }
    }
}

void Board::printCurrentPosition() const
{
    std::cout << "Current State of the game: " << std::endl;
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            std::cout << grid[i][j] << " | ";
        }
        cout << endl;
    }
}

void Board::reset()
{
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            grid[i][j] = 'n';
        }
    }
}

char Board::checkForWinner() const
{
    for (int i = 0; i < 3; ++i)
    {
        // Row check
        if (grid[i][0] != 'n' && grid[i][0] == grid[i][1] && grid[i][1] == grid[i][2])
        {
            return grid[i][0];
        }

        // Column check
        if (grid[0][i] != 'n' && grid[0][i] == grid[1][i] && grid[1][i] == grid[2][i])
        {
            return grid[0][i]; // Fixed: was grid[0][1], should be grid[0][i]
        }
    }

    // Main diagonal
    if (grid[0][0] != 'n' && grid[0][0] == grid[1][1] && grid[1][1] == grid[2][2])
    {
        return grid[0][0];
    }

    // Anti-diagonal
    if (grid[0][2] != 'n' && grid[0][2] == grid[1][1] && grid[1][1] == grid[2][0])
    {
        return grid[0][2];
    }
    return 'n';
}

bool Board::checkForDraw() const
{
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            if (grid[i][j] == 'n')
            {
                return false;
            }
        }
    }
    return true;
}

void Board::setXorO(char type, Uint16 r, Uint16 c)
{
    if (grid[r-1][c-1] == 'n')
    {
        grid[r-1][c-1] = type;
    }
}

Board::~Board()
{
    reset();
}