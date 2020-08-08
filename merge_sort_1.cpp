#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

using namespace std;

template<typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end) {
  if (range_end - range_begin < 2) {
    return;
  }
  vector<typename RandomIt::value_type> elements(range_begin,
      range_end);
  auto t_begin = elements.begin();
  auto t_end = elements.end();
  auto t_half = t_begin + (t_end - t_begin)/2;
  MergeSort(t_begin, t_half);
  MergeSort(t_half, t_end);
  merge(t_begin, t_half, t_half, t_end, range_begin);
}

int main() {
  vector<int> v = {6, 4, 7, 6, 4, 4, 0, 1};
  MergeSort(begin(v), end(v));
  for (int x : v) {
    cout << x << " ";
  }
  cout << endl;
  return 0;
}
