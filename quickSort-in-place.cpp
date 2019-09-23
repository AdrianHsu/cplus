#include <iostream>
#include <cstdio>
#include <random>
using namespace std;

int partition(int arr[], int low, int high) {

  // Step 1. Pick a pivot
  int width = high - low + 1;
  int r = (rand() % width) + low;
  swap(arr[r], arr[low]); 
  int p = arr[low];

  while(low < high) {
    while(low < high && arr[high] >= p) 
      high--;
    arr[low] = arr[high];
    while(low < high && arr[low] <= p)
      low++;
    arr[high] = arr[low];
  }
  arr[low] = p;
  return low;
}

void quickSort(int arr[], int low, int high) {
  if(low < high) {
    int pi = partition(arr, low, high);
    quickSort(arr, low, pi - 1);
    quickSort(arr, pi + 1, high);
  }
}
int main() {
  int arr [] = {7, 10, 8, 1, 9, 5, 6};
  int N = 7;
  quickSort(arr, 0, N - 1);
  for(int i = 0; i < N; i++)
    cout << arr[i] << endl;
  return 0;
}