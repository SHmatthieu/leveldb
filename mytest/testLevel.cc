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
  string value2;

  status = db->Put(leveldb::WriteOptions(), key1, value1);
  printf("val : %s", status.ToString().c_str());
  return 0;
}