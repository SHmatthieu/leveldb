#include <iostream>

#include "leveldb/db.h"

using namespace std;
int main() {
  cout << "levelDB write test !" << endl;

  // create or open the database
  leveldb::DB* db;
  leveldb::Options options;
  options.create_if_missing = true;
  leveldb::Status s = leveldb::DB::Open(options, "./testdb", &db);
  if (!s.ok()) cout << s.ToString() << endl;

  // write values in the database
  s = db->Put(leveldb::WriteOptions(), "key1", "value1");
  cout << (s.ok() ? "put key1 : value1" : s.ToString()) << endl;

  s = db->Put(leveldb::WriteOptions(), "key2", "value2");
  cout << (s.ok() ? "put key2 : value2" : s.ToString()) << endl;

  s = db->Put(leveldb::WriteOptions(), "key3", "value3");
  cout << (s.ok() ? "put key3 : value3" : s.ToString()) << endl;

  return 0;
}