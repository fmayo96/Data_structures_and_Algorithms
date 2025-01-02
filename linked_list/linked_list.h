#pragma once

#include <cstddef>
#include <iostream>
#include <stdexcept>
#include <string>

template <typename T>
struct Node {
  T val;
  Node *next;
  Node<T>() {
    val = 0;
    next = nullptr;
  }
  Node(T value) : val(value) { next = nullptr; }
};

template <typename T>
class LinkedList {
 private:
  size_t count = 1;
  Node<T> *root;
  Node<T> *getNodeAt(int idx) {
    if (idx >= count) {
      std::string errormsg = "[LinkedList.getNodeAt] index ";
      errormsg += std::to_string(idx);
      errormsg += " is out of bounds";
      throw std::out_of_range(errormsg);
    }
    Node<T> *node = root;
    for (int i = 0; i < idx; i++) {
      node = node->next;
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
  size_t size() { return count; }
  T getValAt(int idx) {
    Node<T> *node;
    try {
      node = getNodeAt(idx);
    } catch (std::out_of_range e) {
      std::cout << "[Error]: LinkedList.getValAt | index " << idx
                << " is out of bounds\n";
      return -1;
    }
    return node->val;
  }

  void setValAt(int idx, T value) {
    Node<T> *node;
    try {
      node = getNodeAt(idx);
    } catch (std::out_of_range e) {
      std::cout << "[Error]: LinkedList.setValAt | index " << idx
                << " is out of bounds\n";
    }
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
    ++count;
  }

  void insertBeginnig(T value) {
    Node<T> *new_node = new Node(value);
    new_node->next = root;
    root = new_node;
    ++count;
  }

  void insertAt(int idx, T value) {
    if (idx == 0) insertBeginnig(value);
    Node<T> *new_node = new Node(value);
    Node<T> *iter = root;
    for (int i = 0; i < idx - 1; i++) {
      iter = iter->next;
    }
    new_node->next = iter->next;
    iter->next = new_node;
    ++count;
  }

  void removeEnd() {
    Node<T> *iter = root;
    while (iter->next->next != nullptr) {
      iter = iter->next;
    }
    delete iter->next;
    iter->next = nullptr;
    --count;
  }

  void removeBeginning() {
    Node<T> *aux = root;
    root = root->next;
    delete aux;
    --count;
  }

  void removeAt(int idx) {
    if (idx >= count)
      throw std::out_of_range(
          "[Error]: LinkedList.removeAt | index out of bounds");
    if (idx == 0) removeBeginning();
    Node<T> *prev, *to_delete;
    try {
      prev = getNodeAt(idx - 1);
    } catch (std::out_of_range e) {
      std::cout << "[Error]: LinkedList.removeAt | index " << idx
                << " is out of bounds\n";
    }
    to_delete = prev->next;
    prev->next = to_delete->next;
    delete to_delete;
    --count;
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
