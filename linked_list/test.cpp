#include <iostream>

#include "linked_list.h"

int main() {
  LinkedList<int> list(1);
  list.insertEnd(2);
  list.insertEnd(3);
  list.insertBeginnig(0);
  list.insertAt(2, 4);
  list.Print();
  list.removeAt(5);
  list.Print();
  std::cout << "List size = " << list.size() << "\n";
  return 0;
}
