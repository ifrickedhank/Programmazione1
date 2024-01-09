// HEADERS ---------------------------------------------------------------------
#include <string.h>

#include <fstream>
#include <iostream>

using namespace std;

// STRUTTURE DATI --------------------------------------------------------------
struct Record {
  char* name;
  int grade;
};

struct RecordSet {
  Record* records;
  int size;
};

// FUNZIONI --------------------------------------------------------------------

RecordSet init(int size) { 
  RecordSet rs;
  rs.size = size;
  rs.records = new Record[size];

  for(int i = 0; i < rs.size; i++){
    rs.records[i].name = strdup("");
    rs.records[i].grade = -2;
  }

  return rs; 
}

void drop(RecordSet& rs) {
  delete[] rs.records;
  rs.size = 0;
}

int search(const RecordSet& rs, const char* name);

int insert(RecordSet& rs, const char *name, int grade) { 
   int index = search(rs,strdup(""));
   if( index != -1){

    strcpy(rs.records[index].name , name);
    rs.records[index].grade = grade;
   
    return index;

   }else{

    return -1;
   }
   }

int search(const RecordSet& rs, const char* name) {

  for(int i = 0; i< rs.size; i++){
    if(strcmp(rs.records[i].name, name) == 0){
      return i;
    }
  }
  return -1; 
  }

int update(RecordSet& rs, const char* name, int grade) {
  int index = search(rs,name);
  if(index != -1){
    rs.records[index].grade = grade;
    return index;
  }else
  return -1; 

  }

int remove(RecordSet& rs, const char* name) {
  int index = search(rs,name);
  if(index != -1){
    rs.records[index].name = strdup("");
    rs.records[index].grade = -2;
    return index;
  }else
  return -1; }

RecordSet load(const char* filename) {
  ifstream ifs(filename);
  if (!ifs) {
    cout<<"Errore nell'aprire il file !"<<endl;
    return {nullptr,0};
  }

  int size;
  ifs >> size;

  RecordSet rs;
  rs.size = size; 
  rs.records = new Record[rs.size];

  for (int i = 0; i < rs.size; i++) {
    ifs >> rs.records[i].name >> rs.records[i].grade;
    if(rs.records[i].name == strdup("CANCELLATO")){
      rs.records[i].name = strdup("");
    }
  }

  return rs;
}

int save(const RecordSet& rs, const char* filename) {
  ofstream ofs(filename);
  if (!ofs) {
    return -1;
  }

  ofs << rs.size << endl;
  for (int i = 0; i < rs.size; i++) {
    //Check for null record to save it 
    if(strcmp(rs.records[i].name,strdup("")))
    ofs << "CANCELLATO" << " " << rs.records[i].grade << endl;
    else
    ofs << rs.records[i].name << " " << rs.records[i].grade << endl;
  }

  return rs.size;
  }

#ifndef __TESTS__

int main() {
  
}

#endif
