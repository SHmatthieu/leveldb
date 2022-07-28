#include <iostream>

#include "leveldb/db.h"

using namespace std;
int main() {
  cout << "levelDB read test !" << endl;

  // create or open the database
  leveldb::DB* db;
  leveldb::Options options;
  leveldb::Status s = leveldb::DB::Open(options, "./testdb", &db);
  if (!s.ok()) {
    cout << s.ToString() << endl;
    return -1;
  }

  // read values in the database
  string value;

  s = db->Get(leveldb::ReadOptions(), "key1", &value);
  cout << (s.ok() ? "read key1 : " + value : s.ToString()) << endl;

  s = db->Get(leveldb::ReadOptions(), "key2", &value);
  cout << (s.ok() ? "read key2 : " + value : s.ToString()) << endl;

  s = db->Get(leveldb::ReadOptions(), "key3", &value);
  cout << (s.ok() ? "read key3 : " + value : s.ToString()) << endl;

  s = db->Get(leveldb::ReadOptions(), "key4", &value);
  cout << (s.ok() ? "read key4 : " + value : s.ToString()) << endl;

  return 0;
}