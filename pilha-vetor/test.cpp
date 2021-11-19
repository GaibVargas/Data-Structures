#include <iostream>

int main() {
  using namespace std;

  float *vec = new float[10];

  vec[0] = 0.0;
  vec[1] = 1.0;

  cout << vec[0] << ", " << vec[1] << endl;

  delete [] vec; // para não vazar memória, sempre que tem new tem que ter delete

  return 0;
}