#include "test_runner.h"

#include <algorithm>
#include <iostream>
#include <string>
#include <queue>
#include <stdexcept>
#include <set>
using namespace std;

template <class T>
class ObjectPool {
public:
  T* Allocate() {
    T* object;
    if (deallocate_pool.size() != 0) {
      object = deallocate_pool.front();
      deallocate_pool.pop();
    } else {
      object = new T();
    }
    allocate_pool.insert(object);
    return object;
  }
  T* TryAllocate() {
    T* object;
    if (deallocate_pool.size() != 0) {
      object = deallocate_pool.front();
      deallocate_pool.pop();
    } else {
      object = nullptr;
    }
    allocate_pool.insert(object);
    return object;
  }

  void Deallocate(T* object) {
    auto position = allocate_pool.find(object);
    if (position == allocate_pool.end()) {
      throw invalid_argument("Can't find object");
    }
    deallocate_pool.push(object);
    allocate_pool.erase(position);
  }

  ~ObjectPool() {
    for (auto& item : allocate_pool) {
      delete item;
    }
    allocate_pool.clear();
    while (!deallocate_pool.empty()) {
      delete deallocate_pool.front();
      deallocate_pool.pop();
    }
  }

private:
  set<T*> allocate_pool;
  queue<T*> deallocate_pool;
};

void TestObjectPool() {
  ObjectPool<string> pool;

  auto p1 = pool.Allocate();
  auto p2 = pool.Allocate();
  auto p3 = pool.Allocate();

  *p1 = "first";
  *p2 = "second";
  *p3 = "third";

  pool.Deallocate(p2);
  ASSERT_EQUAL(*pool.Allocate(), "second");

  pool.Deallocate(p3);
  pool.Deallocate(p1);
  ASSERT_EQUAL(*pool.Allocate(), "third");
  ASSERT_EQUAL(*pool.Allocate(), "first");

  pool.Deallocate(p1);
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestObjectPool);
  return 0;
}
