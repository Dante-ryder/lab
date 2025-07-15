#include <iostream>
#include <SDL.h>
#include <SDL_ttf.h>
#include <math.h>
#include <string>

using namespace std;

char arr[3][3] = {{'n', 'n', 'n'}, {'n', 'n', 'n'}, {'n', 'n', 'n'}};

char winner;

const int WINDOW_WIDTH = 640;
const int WINDOW_HEIGHT = 480;

void printCurrentPositions()
{
  std::cout << "Current State of the game: " << std::endl;
  for (int i = 0; i < 3; ++i)
  {
    for (int j = 0; j < 3; ++j)
    {
      std::cout << arr[i][j] << " | ";
    }
    std::cout << std::endl;
    std::cout << "____________";
    std::cout << std::endl;
  }
}

bool checkForWin()
{
  // Row and column checks
  for (int i = 0; i < 3; ++i)
  {
    // Row check
    if (arr[i][0] != 'n' && arr[i][0] == arr[i][1] && arr[i][1] == arr[i][2])
    {
      winner = arr[i][0];
      return true;
    }

    // Column check
    if (arr[0][i] != 'n' && arr[0][i] == arr[1][i] && arr[1][i] == arr[2][i])
    {
      winner = arr[0][1];
      return true;
    }
  }

  // Main diagonal
  if (arr[0][0] != 'n' && arr[0][0] == arr[1][1] && arr[1][1] == arr[2][2])
  {
    winner = arr[0][0];
    return true;
  }

  // Anti-diagonal
  if (arr[0][2] != 'n' && arr[0][2] == arr[1][1] && arr[1][1] == arr[2][0])
  {
    winner = arr[0][2];
    return true;
  }

  return false;
}

void startGame()
{
  int i = 0;
  do
  {
    int rowPos;
    int colPos;
    do
    {
      std::cin >> rowPos;
      std::cin >> colPos;
      if (rowPos > 3 || colPos > 3)
      {
        std::cout << "Invalid Input. Try Entering number 1 - 3" << std::endl;
      }
      if (arr[rowPos - 1][colPos - 1] == 'X' ||
          arr[rowPos - 1][colPos - 1] == 'O')
      {
        std::cout << "That Place was taken plz enter a different pos."
                  << std::endl;
      }
    } while (rowPos > 3 || colPos > 3 || arr[rowPos - 1][colPos - 1] == 'X' ||
             arr[rowPos - 1][colPos - 1] == 'O');
    arr[rowPos - 1][colPos - 1] = i % 2 == 0 ? 'X' : 'O';
    printCurrentPositions();
    i++;
  } while (!checkForWin());
}

// Draw the Tic-Tac-Toe Board
void drawBoard(SDL_Renderer *renderer)
{

  SDL_SetRenderDrawColor(renderer, 162, 162, 162, 162);

  int x = 170, y = 90, size = 300;
  SDL_Rect rect = {
      x,
      y,
      size,
      size};

  SDL_RenderFillRect(renderer, &rect);

  SDL_SetRenderDrawColor(renderer, 0, 0, 255, 0);

  SDL_RenderDrawLine(renderer, 270, 90, 270, 390);

  SDL_RenderDrawLine(renderer, 370, 90, 370, 390);

  SDL_RenderDrawLine(renderer, 170, 190, 470, 190);

  SDL_RenderDrawLine(renderer, 170, 290, 470, 290);
}

void drawX(SDL_Renderer *renderer, int row, int col)
{
  int x = 170 + col * 100;
  int y = 90 + row * 100;

  SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255); // Blue X
  SDL_RenderDrawLine(renderer, x + 20, y + 20, x + 80, y + 80);
  SDL_RenderDrawLine(renderer, x + 80, y + 20, x + 20, y + 80);
}

void drawO(SDL_Renderer *renderer, int row, int col)
{
  int cx = 170 + col * 100 + 50; // center X
  int cy = 90 + row * 100 + 50;  // center Y
  int radius = 30;

  SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255); // Green O

  for (double angle = 0; angle < 2 * M_PI; angle += 0.01)
  {
    int x = (int)(cx + radius * cos(angle));
    int y = (int)(cy + radius * sin(angle));
    SDL_RenderDrawPoint(renderer, x, y);
  }
}

void greetWinner(SDL_Renderer *renderer, char player, TTF_Font *font)
{
  string x = string(1, player) + string(" Wins!");
  SDL_Surface *surface = TTF_RenderText_Solid(font, x.c_str(), {255, 255, 0});
  SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
  SDL_Rect text_rect = {175, 10, 300, 50};
  SDL_FreeSurface(surface);
  SDL_RenderCopy(renderer, texture, NULL, &text_rect);
  SDL_DestroyTexture(texture);
}

void resetBoard()
{
  for (int i = 0; i < 3; ++i)
  {
    for (int j = 0; j < 3; ++j)
    {
      arr[i][j] = 'n';
    }
  }
}

int main()
{
  if (SDL_Init(SDL_INIT_VIDEO) < 0)
  {
    cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << endl;
    return 1;
  }
  SDL_Window *window = SDL_CreateWindow("Tic Tac Toe", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);

  if (!window)
  {
    cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << endl;
    SDL_Quit();
    return 1;
  }

  SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

  if (!renderer)
  {
    std::cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 1;
  }

  SDL_StartTextInput();

  if (TTF_Init() == -1)
  {
    std::cerr << "TTF_Init failed: " << TTF_GetError() << std::endl;
    return 1;
  }
  TTF_Font *font = TTF_OpenFont("resources/fonts/Open_Sans/OpenSans-Italic-VariableFont_wdth,wght.ttf", 24);
  if (!font)
  {
    std::cerr << "Font load failed: " << TTF_GetError() << std::endl;
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    TTF_Quit();
    return 1;
  }

  bool running = 1;
  int i = 0;
  SDL_Event e;
  while (running)
  {
    while (SDL_PollEvent(&e))
    {
      if (e.type == SDL_QUIT)
      {
        running = 0;
      }
      if (e.type == SDL_MOUSEBUTTONDOWN)
      {
        if (checkForWin())
        {
          resetBoard();
          i = 0;
          continue;
        }
        int mx = e.button.x, my = e.button.y;

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
          if (arr[row - 1][col - 1] == 'X' ||
              arr[row - 1][col - 1] == 'O')
          {
            continue;
          }
          if (arr[row - 1][col - 1] == 'n')
          {
            arr[row - 1][col - 1] = (i & 1) ? 'O' : 'X';
            i++;
          }
          printCurrentPositions();
        }
      }
    }

    SDL_SetRenderDrawColor(renderer, 96, 96, 96, 255); // light gray background
    SDL_RenderClear(renderer);

    if (checkForWin())
    {
      greetWinner(renderer, winner, font);
    }

    // Always draw board
    drawBoard(renderer);

    // Redraw all Xs and Os from the board state
    for (int r = 0; r < 3; r++)
    {
      for (int c = 0; c < 3; c++)
      {
        if (arr[r][c] == 'X')
          drawX(renderer, r, c);
        else if (arr[r][c] == 'O')
          drawO(renderer, r, c);
      }
    }

    SDL_RenderPresent(renderer);

    SDL_Delay(16);
  }

  TTF_CloseFont(font);
  TTF_Quit();
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_StopTextInput();

  SDL_Quit();
  return 0;
}