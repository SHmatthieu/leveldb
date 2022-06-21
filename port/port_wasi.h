#ifndef STORAGE_LEVELDB_PORT_PORT_WASI_H_
#define STORAGE_LEVELDB_PORT_PORT_WASI_H_
#include <string>

#include "port/thread_annotations.h"

#include "pthread.h"

namespace leveldb {
namespace port {

class LOCKABLE Mutex {
 public:
  Mutex() { pthread_mutex_init(&mut, NULL); }
  ~Mutex() { pthread_mutex_destroy(&mut); }

  void Lock() EXCLUSIVE_LOCK_FUNCTION() { pthread_mutex_lock(&mut); }

  void Unlock() UNLOCK_FUNCTION() { pthread_mutex_unlock(&mut); }

  void AssertHeld() ASSERT_EXCLUSIVE_LOCK() {}
  pthread_mutex_t mut;
};

class CondVar {
 public:
  explicit CondVar(Mutex* mu) : mymutex(mu) { pthread_cond_init(&cond, NULL); };
  ~CondVar() { pthread_cond_destroy(&cond); }

  void Wait() {
    mymutex->Lock();
    pthread_cond_wait(&cond, &mymutex->mut);
    mymutex->Unlock();
  }

  void Signal() { pthread_cond_signal(&cond); }

  void SignalAll() { pthread_cond_broadcast(&cond); }

 private:
  Mutex* mymutex;
  pthread_cond_t cond;
};

inline bool Snappy_Compress(const char* input, size_t input_length,
                            std::string* output) {
  return false;
}

inline bool Snappy_GetUncompressedLength(const char* input, size_t length,
                                         size_t* result) {
  return false;
}

inline bool Snappy_Uncompress(const char* input_data, size_t input_length,
                              char* output) {
  return false;
}

inline bool GetHeapProfile(void (*func)(void*, const char*, int), void* arg) {
  return false;
}

inline uint32_t AcceleratedCRC32C(uint32_t crc, const char* buf, size_t size) {
  return false;
}

}  // namespace port
}  // namespace leveldb
#endif