// HEADERS ---------------------------------------------------------------------
#include <string.h>

#include <fstream>
#include <iostream>

using namespace std;

// STRUTTURE DATI --------------------------------------------------------------
struct Record {
  char name[128];
  int value;
};

struct RecordSet {
  Record* records;
  int size;
  int capacity;
};

// FUNZIONI --------------------------------------------------------------------

RecordSet init() {
  RecordSet rs;
  rs.records = nullptr;
  rs.size = 0;
  rs.capacity = 0;
  return rs;
}

void drop(RecordSet& rs) {
  if (rs.records != nullptr) {
    delete[] rs.records;
    rs.records = nullptr;
    rs.size = 0;
    rs.capacity = 0;
  }
}

int search(RecordSet& rs, const char* name);

int insert(RecordSet& rs, const char* name, int value) {
  if (search(rs, name) != -1) {
    return -1;
  }
  if (rs.size == rs.capacity) {
    Record* tmp = new Record[rs.capacity * 2];
    for (int i = 0; i < rs.size; i++) {
      tmp[i] = rs.records[i];
    }
    delete[] rs.records;
    rs.records = tmp;
    rs.capacity *= 2;
  }
  strcpy(rs.records[rs.size].name, name);
  rs.records[rs.size].value = value;
  rs.size += 1;
  return rs.size - 1;
  
}

int search(RecordSet& rs, const char* name) {
  for (int i = 0; i < rs.size; i++) {
    if (strcmp(rs.records[i].name, name) == 0) {
      return i;
    }
  }
  return -1;
}

int remove(RecordSet& rs, const char* name) {
  int pos = search(rs, name);
  if (pos == -1) {
    return -1;
  }
  for (int i = pos; i < rs.size - 1; i++) {
    rs.records[i] = rs.records[i + 1];
  }
  rs.size--;
  return pos;
}

int update(RecordSet& rs, const char* name, int value) {
  int pos = search(rs, name);
  if (pos == -1) {
    return -1;
  }
  rs.records[pos].value = value;
  return pos;
}

int load(RecordSet& rs, const char* filename) {
  ifstream ifs(filename);
  if (!ifs) {
    return -1;
  }

  drop(rs);
  ifs >> rs.size;
  rs.capacity = rs.size;
  rs.records = new Record[rs.size];

  for (int i = 0; i < rs.size; i++) {
    ifs >> rs.records[i].name >> rs.records[i].value;
  }

  return rs.size;
}

int save(RecordSet& rs, const char* filename) {
  ofstream ofs(filename);
  if (!ofs) {
    return -1;
  }

  ofs << rs.size << endl;
  for (int i = 0; i < rs.size; i++) {
    ofs << rs.records[i].name << " " << rs.records[i].value << endl;
  }

  return rs.size;
}

#ifndef __TESTS__

int main() {
  // da usare per i vostri tests
  return 0;
}

#endif
