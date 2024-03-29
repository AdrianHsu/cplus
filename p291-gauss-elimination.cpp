#include <vector>
#include <cstdio>
#include <algorithm>
#include <cstdlib>
#include <cmath>
#define EPS 1e-8

using namespace std;
typedef vector<double> vec;
typedef vector<vec> mat;

vec gaussJordon(const mat& A, const vec& b) {
  int n = A.size();
  mat B(n, vec(n + 1));
  for(int i = 0; i < n; i++)
    for(int j = 0; j < n; j++)
      B[i][j] = A[i][j];
  
  for(int i = 0; i < n; i ++)
    B[i][n] = b[i];

  for(int i = 0; i < n; i++){
    int pivot = i;
    for(int j = i; j < n; j++) {
      if(abs(B[j][i]) > abs(B[pivot][i]))
          pivot = j;
    }
    swap(B[i], B[pivot]);

    if(abs(B[i][i]) < EPS) return vec();

    for(int j = 0; j < n; j++) {
      if(i != j) {
        for(int k = i + 1; k <= n; k++) 
        B[j][k] -= B[j][i] * B[i][k];
      }
    }
  }
  vec x(n);
  for(int i = 0; i < n; i++)
    x[i] = B[i][n];
  return x;
}

int main() {
  return 0;
}

