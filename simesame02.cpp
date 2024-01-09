// HEADERS ---------------------------------------------------------------------
#include <string.h>

#include <fstream>
#include <iostream>

using namespace std;

// STRUTTURE DATI --------------------------------------------------------------
struct GameWorld
{
  int* cells;
  int rows;
  int columns;
};

// FUNZIONI --------------------------------------------------------------------

GameWorld init(int r, int c, int* cells) { 
GameWorld game = {new int[r*c],r,c};
if( cells == nullptr){
  for(int i = 0; i< r*c; i++) game.cells[i] = 0;
}else
 for(int i = 0; i< r*c; i++) game.cells[i] = cells[i];

  return game; 
}

void drop(GameWorld &gw) {
  delete[] gw.cells;
  gw.cells = nullptr;
 
  gw.rows = 0;
  gw.columns = 0;
}

int get(const GameWorld &gw, int r, int c) { 
  if(r > (gw.rows-1) || c > (gw.columns-1) || r<0 || c<0){
    return 0;
  }else
  return gw.cells[r*gw.columns+c]; 

  }

void set(GameWorld &gw, int i, int j, int value) {
  gw.cells[i*gw.columns+j] = value;
}

int count(GameWorld &gw, int r, int c){ 
  int co = 0;
    for(int i=-1;i<2;i++){
      /* i are the row*/
      for(int j=-1;j<2;j++){
        /* j are the columns */
          if(get(gw,(r+i),(c+j)) == 1 )
          co+=1;
      }
    }
    if(get(gw,r,c)== 1)
    co -= 1;
    return co;
   }

GameWorld copy(const GameWorld& gw) {
  int* new_cells= new int[gw.rows*gw.columns];
  int rows = gw.rows;
  int columns = gw.columns; 

  for(int i = 0;i <rows*columns ; i++) new_cells[i] = gw.cells[i];
   return {new_cells,rows,columns};
}

void step(GameWorld &gw) {
  GameWorld world_copy = copy(gw);
  /*Sliding the columns*/
  for(int i=0;i<world_copy.columns; i++){
    
    for(int j=0; j<world_copy.rows; j++){
      /*if cell is alive*/
      if(get(gw,j,i)  == 1){
        if(count(gw,j,i) > 4 || count(gw,j,i) <= 1){
          /*cell dies by overpopulation or solitude*/
          set(world_copy,j,i,0); 
        }
      }else{
        /*if cell is dead*/
        if(count(gw,j,i) == 3){
          set(world_copy,j,i,1);
        }

      }
    }
  }
  gw.cells = world_copy.cells;
}
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


#ifndef __TESTS__

int main()
{
  int rows = 4, columns = 4;
  int cells[] = {0, 0, 1, 0, 1, 0, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0};
  GameWorld game = load("simload02.txt");
  print(game);
  

  return 0;
}

#endif
