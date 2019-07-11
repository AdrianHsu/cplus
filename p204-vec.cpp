#include <vector>
#include <cstdio>

using namespace std;

typedef vector<int> vec;
typedef vector<vec> mat;

int main() {
  mat A(3, vec(6));
  mat B(A.size(), vec(4));
  mat C(A.size(), vec(B[0].size()));
  printf("W: %lu; H: %lu\n", C.size(), C[0].size());
  return 0;
}
