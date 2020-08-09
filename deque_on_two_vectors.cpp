#include <iostream>
#include <vector>
#include <iterator>

using namespace std;

template<typename T>
class Deque {
public:
  Deque();
  bool Empty() const;
  size_t Size() const;
  T& operator[](size_t index);
  const T& operator[](size_t index) const;
  T& At(size_t index);
  const T& At(size_t index) const;
  T& Front();
  const T& Front() const;
  T& Back();
  const T& Back() const;
  void PushFront(const T& item);
  void PushBack(const T& item);
private:
  vector<T> front;
  vector<T> back;
};

template<typename T>
Deque<T>::Deque() {}

template<typename T>
bool Deque<T>::Empty() const {
  return front.empty() && back.empty();
}

template<typename T>
void Deque<T>::PushFront(const T& item) {
  front.push_back(item);
}

template<typename T>
void Deque<T>::PushBack(const T& item) {
  back.push_back(item);
}

template<typename T>
size_t Deque<T>::Size() const {
  return front.size() + back.size();
}

template<typename T>
T& Deque<T>::Front() {
  if (front.empty()) {
    return *back.begin();
  }
  return *prev(front.end());
}

template<typename T>
const T& Deque<T>::Front() const {
  if (front.empty()) {
      return *back.begin();
    }
    return *prev(front.end());
}

template<typename T>
T& Deque<T>::Back() {
  if (back.empty()) {
    return *front.begin();
  }
  return *prev(back.end());
}

template<typename T>
const T& Deque<T>::Back() const {
  if (back.empty()) {
      return *front.begin();
    }
    return *prev(back.end());
}

template<typename T>
T& Deque<T>::operator[](size_t index) {
  const size_t front_size = front.size();
  if (index < front.size()) {
    return front[front_size - index - 1];
  } else {
    return back[index - front_size];
  }
}

template<typename T>
const T& Deque<T>::operator[](size_t index) const {
  const size_t front_size = front.size();
  if (index < front.size()) {
    return front[front_size - index - 1];
  } else {
    return back[index - front_size];
  }
}

template<typename T>
T& Deque<T>::At(size_t index) {
  if (index >= Size()) {
    throw out_of_range("");
  }
  const size_t front_size = front.size();
    if (index < front.size()) {
      return front[front_size - index - 1];
    } else {
      return back[index - front_size];
    }
}

template<typename T>
const T& Deque<T>::At(size_t index) const {
  if (index >= Size()) {
    throw out_of_range("");
  }
  const size_t front_size = front.size();
    if (index < front.size()) {
      return front[front_size - index - 1];
    } else {
      return back[index - front_size];
    }
}

int main(void) {
  Deque<double> d;
  d.PushBack(19);
  d.PushFront(1);
  cout << d.At(2) << endl;
}





