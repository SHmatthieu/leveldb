#include <chrono>
#include <iostream>
#include <sstream>
#include <string>

#include "leveldb/db.h"

static int ITER = 10000;

using namespace std;

class Bench {
 private:
  chrono::high_resolution_clock::time_point t1;
  double total;
  int iter;
  string mode;
  stringstream buffer;
  leveldb::DB* db;

 public:
  Bench(int it) : iter(it) {
    leveldb::Options options;
    options.create_if_missing = true;
    leveldb::DB::Open(options, "./benchdb", &db);
  }
  void Write() {
    mode = "Write";
    Start();
    for (int i = 0; i < iter; i++) {
      char key[100];
      std::snprintf(key, sizeof(key), "%016d", i);
      std::string cpp_key = key;

      leveldb::WriteOptions write_options;
      write_options.sync = true;
      db->Put(write_options, cpp_key, "value");

      FinishedSingleOp();
    }
    PrintResult();
  }

  void Read() {
    mode = "Read";
    Start();
    for (int i = 0; i < iter; i++) {
      string value;
      char key[100];
      std::snprintf(key, sizeof(key), "%016d", i);
      std::string cpp_key = key;
      db->Get(leveldb::ReadOptions(), cpp_key, &value);

      FinishedSingleOp();
    }
    PrintResult();
  }

  void Start() {
    t1 = chrono::high_resolution_clock::now();
    total = 0;
  }
  void FinishedSingleOp() {
    chrono::high_resolution_clock::time_point t2 =
        chrono::high_resolution_clock::now();
    chrono::duration<double, std::milli> time_span =
        chrono::duration_cast<chrono::duration<double, std::milli>>(t2 - t1);
    total += time_span.count();
    t1 = t2;
  }

  void PrintResult() {
    buffer << mode << " took : " << total << " ms. ";
    buffer << "to do " << iter << " iterations." << endl;
  }

  void GetResult() { cout << buffer.str(); }
};

int main(void) {
  cout << "benchmarks leveldb !" << endl;

  Bench bench(ITER);
  bench.Write();
  bench.Read();
  bench.GetResult();

  return 0;
}
