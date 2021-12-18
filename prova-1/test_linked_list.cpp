#include <iostream>
#include "linked_list.h"

int main() {
  structures::LinkedList<int> lista;
  for (auto i = 0u; i < 7; i++) {
    lista.push_back(i);
  }
  std::cout << lista.size() << '\n';

  auto lista_halve = lista.halve();
  std::cout << lista_halve.size() << '\n';
  std::cout << lista_halve.at(0)->at(0) << '\n';
  std::cout << lista_halve.at(1)->at(0) << '\n';
}