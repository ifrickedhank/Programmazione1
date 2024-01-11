// HEADERS ---------------------------------------------------------------------
#include <string.h>

#include <fstream>
#include <iostream>

using namespace std;

// STRUTTURE DATI --------------------------------------------------------------
struct Record
{
  char name[128];
  int value;
};

struct RecordSet
{
  Record *records;
  int size;
  int capacity;
};

// FUNZIONI --------------------------------------------------------------------

RecordSet init() { return {new Record[8], 0, 8}; }

void drop(RecordSet &rs)
{
  delete[] rs.records;
}

int insert(RecordSet &rs, const char *name, int value)
{
  int exists = 0;
  if (rs.capacity == rs.size)
  {
    RecordSet big = {new Record[8 * 2], rs.size, rs.capacity * 2};
    for (int i = 0; i < rs.size; i++)
    {
      big.records[i] = rs.records[i];
    }
    drop(rs);
    rs = big;
  }
  for (int i = 0; i < rs.size; i++)
  {
    if (0 == strcmp(rs.records[i].name, name))
    {
      exists = 1;
    }
  }
  if (exists == 1)
  {
    return -1;
  }
  else
  { 
    strcpy(rs.records[rs.size].name,name);
    rs.records[rs.size].value=value;
    rs.size+=1;
    return rs.size-1;
  }
}

int search(RecordSet &rs, const char *name) {
  for (int i = 0; i < rs.size; i++)
  {
    if (0 == strcmp(rs.records[i].name, name))
    {
      return i;
    }
  }
  return -1;
  }

int remove(RecordSet &rs, const char *name) { 
  int exists=search(rs,name);
  if(-1!=exists){
    for(int i=exists;i<rs.size-1;i++){
        rs.records[i]=rs.records[i+1];
    }
    rs.size--;
    return exists;
  }else{
    return -1;
  }
 }

int update(RecordSet &rs, const char *name, int value) { 
  int exists=search(rs,name);
  if(-1!=exists){
    rs.records[exists].value=value;
    return exists;
  }else{
    return -1;
  }
}

int load(RecordSet &rs, const char *filename) { 
  ifstream f(filename);
  int n=0;
  f>>n;
  char name;
  int value;
  while(!cin.eof()){
    f>>name;
    f>>value;
    insert(rs,name,value);
  }
  return n;
}

int save(RecordSet &rs, const char *filename) { return -2; }

#ifndef __TESTS__

int main()
{
  // da usare per i vostri tests
  return 0;
}

#endif
