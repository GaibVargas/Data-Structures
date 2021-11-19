#include <iostream>
#include "array_queue.h"

using namespace structures;
using namespace std;

int main() {
  auto queue = ArrayQueue<int>();
  
  queue.enqueue(2);
  queue.enqueue(3);

  auto first = queue.dequeue();
  auto second = queue.dequeue();

  queue.enqueue(4);

  cout << first << second << endl;
}