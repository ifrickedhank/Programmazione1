// HEADERS ---------------------------------------------------------------------
#include <string.h>

#include <fstream>
#include <iostream>

using namespace std;

// STRUTTURE DATI --------------------------------------------------------------
struct GameWorld
{
  int *cells;
  int rows;
  int columns;
};

// FUNZIONI --------------------------------------------------------------------

GameWorld init(int n, int m, int *cells)
{
  int *celle;
  if (cells == nullptr)
  {
    celle = new int[n * m];
    for (int i = 0; i < n * m; i++)
    {
      celle[i] = 0;
    }
  }
  else
  {
    celle = cells;
  }
  GameWorld game = {celle, n, m};
  return game;
}

void drop(GameWorld &gw)
{
  delete[] gw.cells;
  gw.rows = 0;
  gw.columns = 0;
}

int get(const GameWorld &gw, int i, int j)
{
  if (i >= gw.rows || j >= gw.columns || i < 0 || j < 0)
  {
    return 0;
  }
  return gw.cells[gw.rows * i + j];
}

void set(GameWorld &gw, int i, int j, int value)
{
  gw.cells[gw.columns * i + j] = value;
}

int count(GameWorld &gw, int i, int j)
{
  int c = 0;
  // up
  if (get(gw, i - 1, j) == 1)
  {
    c++;
  }
  // up right
  if (get(gw, i - 1, j + 1) == 1)
  {
    c++;
  }
  // up left
  if (get(gw, i - 1, j - 1) == 1)
  {
    c++;
  }
  // right
  if (get(gw, i, j + 1) == 1)
  {
    c++;
  }
  // left
  if (get(gw, i, j - 1) == 1)
  {
    c++;
  }
  // down
  if (get(gw, i + 1, j) == 1)
  {
    c++;
  }
  // down left
  if (get(gw, i + 1, j - 1) == 1)
  {
    c++;
  }
  // down right
  if (get(gw, i + 1, j + 1) == 1)
  {
    c++;
  }
  return c;
}

GameWorld copy(const GameWorld &gw)
{
  int *celle;

  celle = new int[gw.rows * gw.columns];
  for (int i = 0; i < gw.rows * gw.columns; i++)
  {
    celle[i] = gw.cells[i];
  }
  return init(gw.rows, gw.columns, celle);
}

void step(GameWorld &gw)
{
  GameWorld old = copy(gw);
  for (int r = 0; r < gw.rows; r++)
    for (int c = 0; c < gw.columns; c++)
    {
      if (get(old, r, c) == 0 && count(old, r, c) == 3)
      {
        set(gw, r, c, 1);
      }
      else if (!(count(old, r, c) == 3 || count(old, r, c) == 2))
      {
        set(gw, r, c, 0);
      }
    }
}

GameWorld load(const char *filename)
{
  ifstream f(filename);
  if(!f)return {};
  int r, c;
  f >> r >> c;
  int *celle = new int[r * c];
  for (int i = 0; i <r * c; i++)
  {
    f >> celle[i];
  }
  return init(r, c, celle);
}

int save(const GameWorld &gw, const char *filename) {
  ofstream f(filename);
  f << gw.rows <<" "<<gw.columns << endl;
  for (int r = 0; r < gw.rows; r++){
    for (int c = 0; c < gw.rows; c++)
      f << get(gw,r,c)<<" ";
    f<<endl;
  }  
    
   return 0; }

void print(const GameWorld &gw)
{
  printf("GameWorld %d x %d\n", gw.rows, gw.columns);
  for (int i = 0; i < gw.rows; i++)
  {
    for (int j = 0; j < gw.columns; j++)
    {
      printf("%d ", get(gw, i, j));
    }
    printf("\n");
  }
  printf("\n");
}

#ifndef __TESTS__

int main()
{
  // da usare per i vostri tests
  return 0;
}

#endif
