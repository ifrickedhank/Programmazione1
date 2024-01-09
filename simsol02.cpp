// HEADERS ---------------------------------------------------------------------
#include <string.h>

#include <fstream>
#include <iostream>

using namespace std;

// STRUTTURE DATI --------------------------------------------------------------
struct GameWorld {
  int* cells;
  int rows;
  int columns;
};

// FUNZIONI --------------------------------------------------------------------

int get(const GameWorld& gw, int i, int j) {
  if (i < 0 || i >= gw.rows || j < 0 || j >= gw.columns) return 0;
  return gw.cells[i * gw.columns + j];
}

void set(GameWorld& gw, int i, int j, int value) {
  if (i < 0 || i >= gw.rows || j < 0 || j >= gw.columns) return;
  gw.cells[i * gw.columns + j] = value;
}

int count(GameWorld& gw, int i, int j) {
  int count = 0;
  for (int k = i - 1; k <= i + 1; k++)
    for (int l = j - 1; l <= j + 1; l++)
      if (k != i || l != j) count += get(gw, k, l);
  return count;
}

GameWorld copy(const GameWorld& gw) {
  GameWorld gw2;
  gw2.rows = gw.rows;
  gw2.columns = gw.columns;
  gw2.cells = new int[gw.rows * gw.columns];
  for (int i = 0; i < gw.rows * gw.columns; i++) gw2.cells[i] = gw.cells[i];
  return gw2;
}

GameWorld init(int n, int m, int* cells) {
  GameWorld gw;
  gw.rows = n;
  gw.columns = m;
  gw.cells = new int[n * m];
  if (cells != nullptr) {
    for (int i = 0; i < n * m; i++) gw.cells[i] = cells[i];
  } else {
    for (int i = 0; i < n * m; i++) gw.cells[i] = 0;
  }
  return gw;
}

void drop(GameWorld& gw) {
  delete[] gw.cells;
  gw.cells = nullptr;
  gw.rows = 0;
  gw.columns = 0;
}

int step(GameWorld& gw) {
  GameWorld gw2 = copy(gw);
  int changes = 0;
  for (int i = 0; i < gw.rows; i++) {
    for (int j = 0; j < gw.columns; j++) {
      int c = count(gw, i, j);
      int v = get(gw, i, j);
      if (v == 0 && c == 3) {
        set(gw2, i, j, 1);
        changes++;
      } else if (v == 1 && (c < 2 || c > 3)) {
        set(gw2, i, j, 0);
        changes++;
      }
    }
  }
  drop(gw);
  gw = gw2;
  return changes;
}

GameWorld load(const char* filename) {
  ifstream ifs(filename);
  if (!ifs) return init(0, 0, nullptr);
  int n, m;
  ifs >> n >> m;
  int* cells = new int[n * m];
  for (int i = 0; i < n * m; i++) ifs >> cells[i];
  GameWorld gw = init(n, m, cells);
  delete[] cells;
  return gw;
}

int save(const GameWorld& gw, const char* filename) {
  ofstream ofs(filename);
  if (!ofs) return -1;
  ofs << gw.rows << " " << gw.columns << endl;
  for (int i = 0; i < gw.rows; i++) {
    for (int j = 0; j < gw.columns; j++) {
      ofs << get(gw, i, j) << " ";
    }
    ofs << endl;
  }
  return 0;
}

void print(const GameWorld& gw) {
  printf("GameWorld %d x %d\n", gw.rows, gw.columns);
  for (int i = 0; i < gw.rows; i++) {
    for (int j = 0; j < gw.columns; j++) {
      printf("%d ", get(gw, i, j));
    }
    printf("\n");
  }
  printf("\n");
}

#ifndef __TESTS__

int main() {
  // da usare per i vostri tests
  return 0;
}

#endif
