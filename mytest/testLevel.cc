#include <iostream>

#include "leveldb/db.h"

using namespace std;
int main() {
  printf("test leveldb \n");

  leveldb::DB* db;
  leveldb::Options options;
  options.create_if_missing = true;
  leveldb::Status status = leveldb::DB::Open(options, "./testdb", &db);
  printf("status : %s\n", status.ToString().c_str());

  string key1 = "name";
  string value1 = "matthieu";
  string key2 = "age";
  string value3 = "21";
  string value2;

  status = db->Put(leveldb::WriteOptions(), key1, value1);
  printf("val : %s\n", status.ToString().c_str());
  status = db->Get(leveldb::ReadOptions(), key1, &value2);
  printf("val : %s\n", status.ToString().c_str());
  printf("val : %s\n", value2.c_str());
  cout << "test" << endl;

  return 0;
}