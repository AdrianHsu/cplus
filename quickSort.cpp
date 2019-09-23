#include <iostream>
#include <cstdio>
#include <random>

using namespace std;

int partition(vector<int>& nums, int low, int high) {
  // Step 1. Pick a pivot
  int width = high - low + 1;
  int r = (rand() % width) + low;
  swap(nums[r], nums[high]); // 放到最後面，方便處理 
  int pivot = nums[high];


  // Step 2. left < pivot,  right > pivot
  vector<int> lower;
  vector<int> higher;
  for(int i = low; i < high; i++) {
    if(nums[i] <= pivot) {
      lower.push_back(nums[i]);
    } else {
      higher.push_back(nums[i]);
    }
  }

  int cnt = 0;
  int pi = 0;
  for(int i = low; i <= high; i++, cnt++) {
    if(cnt < lower.size()) {
      nums[i] = lower[cnt];
    } else if(cnt == lower.size()) {
      nums[i] = pivot;
      pi = i;
    } else {
      nums[i] = higher[cnt - 1 - lower.size()];
    }
  }

  return pi;
}

void quickSort(vector<int>& nums, int low, int high) {
  if(low < high) {
    int pi = partition(nums, low, high);
    quickSort(nums, low, pi - 1);
    quickSort(nums, pi + 1, high);
  }
}

int main() {
  vector<int> nums;
  int arr[]= {18, 60, 20, 17, 30, 59, 91, 20, 49, 33, 60};
  int N = 11;

  for(int i = 0; i < N; i++)
    nums.push_back(arr[i]);
  quickSort(nums, 0, N - 1);

  for(int i = 0; i < N; i++)
    cout << nums[i] << endl;
  return 0;
}