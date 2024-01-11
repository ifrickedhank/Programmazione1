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
  Record* records=new Record[size];
  for(int i=0;i<size;i++){
      records[i].name=strdup("");
      records[i].grade=-2;
    }
  return {records,size}; }

void drop(RecordSet& rs) {
  rs.size=0;
  delete[] rs.records;
}
int search(const RecordSet& rs, const char* name) { 
  for(int i=0;i<rs.size;i++){
    if(strcmp(rs.records[i].name,name)==0){
      return i;
    }
  }
  return -1;
 }

int insert(RecordSet& rs, const char* name, int grade) { 
  
  if(search(rs,name)==-1){
    for(int i=0;i<rs.size;i++){
      if(rs.records[i].grade==-2){
        rs.records[i].grade=grade;
        strcpy(rs.records[i].name,name);
        
        return i;
      }
    }
    
    return -1;
  }
  return -1;
}



int update(RecordSet& rs, const char* name, int grade) { 
  int position=search(rs,name);
  if(position!=-1){
    rs.records[position].grade=grade;
    return position;
  }
  return -1;
}

int remove(RecordSet& rs, const char* name) { 
  int position=search(rs,name);
  if(position!=-1){
    rs.records[position].grade=-2;
    rs.records[position].name=strdup("");
    return position;
  }
  return -1;
}

RecordSet load(const char* filename) { 
  ifstream f(filename);
  int size,grade;
  char* name=new char[512];
  f>>size;
  RecordSet rs=init(size);
  for(int i=0;i<size;i++){
    f>>name;
    f>>grade;
    if(strcmp(name,"CANCELLATO")==0){
      rs.records[i].name=strdup("");
    }else{
      strcpy(rs.records[i].name,name);
    }
    rs.records[i].grade=grade;
  }
  return rs;
 }

int save(const RecordSet& rs, const char* filename) { 
  ofstream f(filename);
  if(!f){
    return -1;
  }
  f<<rs.size<<endl;
  for(int i=0;i<rs.size;i++){
    if(rs.records[i].grade==-2)
      f<<"CANCELLATO "<<rs.records[i].grade<<endl;
    else
      f<<rs.records[i].name<<" "<<rs.records[i].grade<<endl;
  }
  return 1;
 }

#ifndef __TESTS__

int main() {
  // da usare per i vostri tests
  return 0;
}

#endif
