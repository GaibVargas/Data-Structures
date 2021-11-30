#ifndef STRUCTURES_LINKED_STACK
#define STRUCTURES_LINKED_STACK
//! Copyright [2021] Gabriel de Vargas Coelho

#include <stdexcept>

namespace structures {

//! Classe pilha encadeada
template<typename T>
class LinkedStack {
 public:
  //! Construtor
  LinkedStack();
  //! Destrutor
  ~LinkedStack();
  //! Limpa pilha
  void clear();
  //! Empilha
  void push(const T& data);
  //! Desempilha
  T pop();
  //! Topo
  T& top() const;
  //! Verifica pilha vazia
  bool empty() const;
  //! Tamanho
  std::size_t size() const;

 private:
  //! Classe nó
  class Node {
   public:
    //! Construtor
    explicit Node(const T& data):
      data_{data}
    {}
    //! Construtor parametrizado
    Node(const T& data, Node* next):
      data_{data},
      next_{next}
    {}
    //! Retorna dado
    T& data() {
      return data_;
    }
    //! Retorna dado const
    const T& data() const {
      return data_;
    }
    //! Retorna próximo
    Node* next() {
      return next_;
    }
    //! Retorna próximo
    const Node* next() const {
      return next_;
    }
    //! Setta próximo
    void next(Node* next) {
      next_ = next;
    }

   private:
    //! Dado
    T data_;
    //! Próximo nó
    Node* next_{nullptr};
  };
  //! Topo
  Node* top_{nullptr};
  //! Tamanho
  std::size_t size_{0u};
};

}  //  namespace structures

template<typename T>
structures::LinkedStack<T>::LinkedStack() {
  top_ = nullptr;
  size_ = 0;
}

template<typename T>
structures::LinkedStack<T>::~LinkedStack() {
  clear();
}

template<typename T>
void structures::LinkedStack<T>::clear() {
  Node* current = top_;
  while (current != nullptr) {
    auto next = current->next();
    delete current;
    current = next;
  }
  top_ = nullptr;
  size_ = 0;
}

template<typename T>
void structures::LinkedStack<T>::push(const T& data) {
  Node* new_top = new Node(data, top_);
  if (new_top == nullptr) {
    throw std::out_of_range("Pilha cheia");
  }
  top_ = new_top;
  size_++;
}

template<typename T>
T structures::LinkedStack<T>::pop() {
  if (empty()) {
    throw std::out_of_range("Pilha vazia");
  }
  auto previous_head = top_;
  auto data = previous_head->data();
  top_ = previous_head->next();
  size_--;
  delete previous_head;
  return data;
}

template<typename T>
T& structures::LinkedStack<T>::top() const {
  if (empty()) {
    throw std::out_of_range("Pilha vazia");
  }
  return top_->data();
}

template<typename T>
bool structures::LinkedStack<T>::empty() const {
  return size_ == 0;
}

template<typename T>
std::size_t structures::LinkedStack<T>::size() const {
  return size_;
}

#endif
