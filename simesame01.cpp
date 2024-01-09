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
  delete[] rs.records;
  rs.size = 0;
  rs.capacity = 0;
}
//declare the function before its used so i can set it later but its callable
int search(RecordSet& rs, const char* name);

int insert(RecordSet& rs, const char* name, int value) { 
  // Checks if record exists 
  if(search(rs,name) != -1) 
  return -1;
  // controls that the array isn't already full
  if(rs.size == rs.capacity){
    // Create a new Record array of double the size
    Record* temp = new Record[rs.capacity *2];
     for (int i = 0; i < rs.size; i++) {
      temp[i] = rs.records[i];
    }

    // delete all the records 
    delete[] rs.records;
    rs.records = temp;
    // set the size to double that
    rs.capacity = rs.capacity*2;

  }
    // checks that the name we want to add isn't too long 
    if(sizeof(rs.records->name) < sizeof(name))
    return -1;

    //adds the record and increases the size value by 1
    strcpy(rs.records[rs.size].name, name);
    // to copy a const use the function ABOVE
    rs.records[rs.size].value = value;
    rs.size += 1;
    return rs.size - 1;
  

}

int search(RecordSet& rs, const char* name) {
  for(auto i = 0 ;i < rs.size; i++){
    // to compare char arrays use the strcmp function
    if(strcmp(rs.records[i].name, name) == 0){
      return i;
    }
  }
  return -1;
 }

int remove(RecordSet& rs, const char* name) { 
  int pos = search(rs, name);
  // controls that the given record exits
  if (pos == -1) {
    return -1;
  }
  //sets, starting from the index of the record, record[i] = record[i+1]
  for (int i = pos; i < rs.size - 1; i++) {
    rs.records[i] = rs.records[i + 1];
  }
  // reduces the size by one
  rs.size--;
  return pos;
 }

int update(RecordSet& rs, const char* name, int value) { 
   int pos = search(rs, name);
    if(pos == -1)
      return -1; 

    rs.records[pos].value = value;
    return pos;   
}
void print(RecordSet& rs);


int load(RecordSet& rs, const char* filename) {
  // sets the endpoint 
  ifstream ifs(filename);
  //controls if it exists 
  if (!ifs) {
    cout<<"Dint find the file"<<endl;
    return -1;
  }

  //deletes the current record array
  drop(rs);
  // loads the size 
  ifs >> rs.size;
  // for memory purpose it sets the capacity = to size 
  rs.capacity = rs.size;
  rs.records = new Record[rs.size];
  // memorizes all of the records
  for (int i = 0; i < rs.size; i++) {
    ifs >> rs.records[i].name >> rs.records[i].value;
  }
  
  //and returns the loaded record
  return rs.size;
 }

int save(RecordSet& rs, const char* filename) {
  //sets the endpoint
  ofstream ofs(filename);
  if (!ofs) {
    return -1;
  }
  //writes the size 
  ofs << rs.size << endl;
  //then it writes all of the record like this
  // "record_name"<space>"value"
  for (int i = 0; i < rs.size; i++) {
    ofs << rs.records[i].name << " " << rs.records[i].value << endl;
  }
  
  return rs.size; }

void print(RecordSet& rs){
  for(int i=0;i<rs.size; i++){
    cout<<rs.records[i].name<<" "<<rs.records[i].value<<endl;
  }
}
#ifndef __TESTS__

int main() {
  RecordSet rs = {nullptr,0,0}; 
  
  int size = load(rs, "simload01.txt") ;
  print(rs);
  
  return 0;
}

#endif
