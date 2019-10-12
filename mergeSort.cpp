#include <iostream>
#include <vector>

using namespace std;

vector<int> mergeSort(vector<int> arr, int N) {
  if(arr.size() == 1) return arr;
  int mid = N >> 1;
  vector<int> l = mergeSort(vector<int>(arr.begin(), arr.begin() + mid), mid);
  vector<int> r = mergeSort(vector<int>(arr.begin() + mid, arr.end()), N - mid);

  int i = 0, j = 0, k = 0;
  while(i < l.size() && j < r.size()) {
    if(l[i] <= r[j]) {
      arr[k++] = l[i++];
    } else {
      arr[k++] = r[j++];
    }
  }
  while(i < l.size())
    arr[k++] = l[i++];
  while(j < r.size())
    arr[k++] = r[j++];

  return arr;
}

int main() {
  int N = 11;
  int nums[] = {18, 20, 39, 6, 32, 51, 10, 5, 26, 1, 45};
  vector<int> arr;
  for(int v: nums)
    arr.push_back(v);
  vector<int> vec = mergeSort(arr, N);
  for(int v: vec)
    cout << v << endl;

  return 0;
}
