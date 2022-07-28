#include <iostream>

#include "leveldb/db.h"
#include "leveldb/write_batch.h"

using namespace std;
int main() {
  printf("test leveldb \n");

  // create the database
  leveldb::DB* db;
  leveldb::Options options;
  options.create_if_missing = true;
  leveldb::Status s = leveldb::DB::Open(options, "./testdb", &db);
  if (!s.ok()) cout << s.ToString() << endl;

  string value2;

  leveldb::WriteOptions write_options;
  write_options.sync = true;

  s = db->Put(write_options, "key1", "matthieu");
  if (!s.ok()) cout << s.ToString() << endl;
  cout << "put -> key1 : matthieu" << endl;

  s = db->Get(leveldb::ReadOptions(), "key1", &value2);
  if (!s.ok()) cout << s.ToString() << endl;
  cout << "get -> key1 : " << value2 << endl;

  return 0;
}