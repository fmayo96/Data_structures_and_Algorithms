#include <iostream>
#include <stdexcept>
#include <string>

template <typename T> struct Node {
  T val;
  Node *next;
  Node<T>() {
    val = 0;
    next = nullptr;
  }
  Node(T value) : val(value) { next = nullptr; }
};

template <typename T> class LinkedList {
private:
  Node<T> *root;
  Node<T> *getNodeAt(int idx) {
    Node<T> *node = root;
    for (int i = 0; i < idx; i++) {
      node = node->next;
      if (node == nullptr) {
        std::string errormsg = "[LinkedList.getNodeAt] index ";
        errormsg += std::to_string(idx);
        errormsg += " is out of bounds";
        throw std::out_of_range(errormsg);
      }
    }
    return node;
  }

public:
  LinkedList<T>() { root = new Node<T>; }
  LinkedList(T value) { root = new Node<T>(value); }
  ~LinkedList() {
    Node<T> *iter = root;
    while (iter != nullptr) {
      Node<T> *aux = iter;
      iter = iter->next;
      delete aux;
    }
  }
  T getValAt(int idx) {
    Node<T> *node;
    try {
      node = getNodeAt(idx);
    } catch (std::out_of_range e) {
      std::cout << "[LinkedList.getValAt] index " << idx
                << " is out of bounds\n";
      return -1;
    }
    return node->val;
  }
  void setValAt(int idx, T value) {
    Node<T> *node = getNodeAt(idx);
    node->val = value;
  }
  void insertEnd(T value) {
    Node<T> *new_node = new Node<T>;
    new_node->val = value;
    Node<T> *iter = root;
    while (iter->next != nullptr) {
      iter = iter->next;
    }
    iter->next = new_node;
  }
  void Print() {
    Node<T> *iter = root;
    while (iter != nullptr) {
      std::cout << iter->val << " ";
      iter = iter->next;
    }
    std::cout << "\n";
  }
};

int main() {

  LinkedList<int> list(1);
  list.insertEnd(2);
  list.insertEnd(3);
  list.Print();
  list.getValAt(0);
  list.getValAt(3);
  return 0;
}
