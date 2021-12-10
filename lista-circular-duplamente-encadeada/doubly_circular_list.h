//! Copyright [2021] Gabriel de Vargas Coelho
#ifndef STRUCTURES_LINKED_LIST_H
#define STRUCTURES_LINKED_LIST_H

#include <cstdint>

namespace structures {

//! Classe lista encadeada
template<typename T>
class DoublyCircularList {
 public:
  //! Construtor
  DoublyCircularList();  // construtor padrão
  //! Destrutor
  ~DoublyCircularList();  // destrutor
  //! Limpa a lista
  void clear();  // limpar lista
  //! Insere no fim
  void push_back(const T& data);  // inserir no fim
  //! Insere no início
  void push_front(const T& data);  // inserir no início
  //! Insere na posição
  void insert(const T& data, std::size_t index);  // inserir na posição
  //! Insere na ordem
  void insert_sorted(const T& data);  // inserir em ordem
  //! Acessa na posição constante
  T& at(std::size_t index);  // acessar um elemento na posição index
  //! Retira da posição
  T pop(std::size_t index);  // retirar da posição
  //! Retira do fim
  T pop_back();  // retirar do fim
  //! Retira do início
  T pop_front();  // retirar do início
  //! Retira específico
  void remove(const T& data);  // remover específico
  //! Verifica lista vazia
  bool empty() const;  // lista vazia
  //! Verifica se contém
  bool contains(const T& data) const;  // contém
  //! Posição do data
  std::size_t find(const T& data) const;  // posição do data
  //! Tamanho da lista
  std::size_t size() const;  // tamanho da lista

 private:
    //! Classe nó
  class Node {
   public:
    //! Construtor
    explicit Node(const T& data):
      data_{data}
    {}
    //! Construtor, próximo parametrizado
    Node(const T& data, Node* next):
      data_{data},
      next_{next}
    {}
    //! Construtor parametrizado
    Node(const T& data, Node* prev, Node* next):
      data_{data},
      prev_{prev},
      next_{next}
    {}
    //! Dado
    T& data() {
      return data_;
    }
    //! Dado (const)
    const T& data() const {
      return data_;
    }
    //! Antecessor
    Node* prev() {
      return prev_;
    }
    //! Antecessor (const)
    const Node* prev() const {
      return prev_;
    }
    //! Atribui antecessor
    void prev(Node* node) {
      prev_ = node;
    }
    //! Próximo
    Node* next() {
      return next_;
    }
    //! Próximo (const)
    const Node* next() const {
      return next_;
    }
    //! Atribui próximo
    void next(Node* node) {
      next_ = node;
    }

   private:
    //! Dado
    T data_;
    //! Antecessor
    Node* prev_{nullptr};
    //! Próximo
    Node* next_{nullptr};
  };

  //! Primeiro elemento da lista
  Node* head{nullptr};
  //! Tamanho da lista
  std::size_t size_{0u};
};

}  // namespace structures

template<typename T>
structures::DoublyCircularList<T>::DoublyCircularList() {
  size_ = 0;
  head = nullptr;
}

template<typename T>
structures::DoublyCircularList<T>::~DoublyCircularList() {
  clear();
}

template<typename T>
void structures::DoublyCircularList<T>::clear() {
  Node* current = head;
  while (size() != 0) {
    auto next = current->next();
    delete current;
    current = next;
    size_--;
  }
  head = nullptr;
}

template<typename T>
void structures::DoublyCircularList<T>::push_back(const T& data) {
  Node* element = new Node(data);
  if (element == nullptr) {
    throw std::out_of_range("Lista cheia");
  }
  if (size() == 0) {
    element->next(element);
    element->prev(element);
    head = element;
  } else {
    element->next(head);
    element->prev(head->prev());
    head->prev()->next(element);
    head->prev(element);
  }
  size_++;
}

template<typename T>
void structures::DoublyCircularList<T>::push_front(const T& data) {
  Node* element = new Node(data);
  if (element == nullptr) {
    throw std::out_of_range("Lista cheia");
  }
  if (size() == 0) {
    element->next(element);
    element->prev(element);
    head = element;
  } else {
    element->next(head);
    element->prev(head->prev());
    head->prev()->next(element);
    head->prev(element);
    head = element;
  }
  size_++;
}

template<typename T>
void structures::DoublyCircularList<T>::insert(
	const T& data, std::size_t index
) {
  if (index > size()) {
    throw std::out_of_range("Índice fora do limite");
  }
  if (index == 0) {
    return push_front(data);
  }
  if (index == size()) {
    return push_back(data);
  }
  Node* element = new Node(data);
  if (element == nullptr) {
    throw std::out_of_range("Lista cheia");
  }
  auto pos = 0u;
  auto current = head;
  while (pos < index - 1) {
    current = current->next();
    pos++;
  }
  element->next(current->next());
  element->prev(current);
  current->next()->prev(element);
  current->next(element);
  size_++;
}

template<typename T>
void structures::DoublyCircularList<T>::insert_sorted(const T& data) {
	if (size() == 0) {
		return push_front(data);
	}
	auto current = head;
	auto pos = 0u;
	while (
		current->next() != nullptr &&
		current->next() != head &&
		data > current->data()
	) {
		current = current->next();
		pos++;
	}
	if (data > current->data()) {
		return insert(data, pos + 1);
	} else {
		return insert(data, pos);
	}
}

template<typename T>
T& structures::DoublyCircularList<T>::at(std::size_t index) {
	if (index > size() - 1) {
		throw std::out_of_range("Índice fora do limite");
	}
	auto current = head;
	for (auto i = 0u; i < index; i++) {
		current = current->next();
	}
	return current->data();
}

template<typename T>
T structures::DoublyCircularList<T>::pop(std::size_t index) {
  if (empty()) {
    throw std::out_of_range("Lista vazia");
  }
  if (index > size() - 1) {
    throw std::out_of_range("Índice fora do limite");
  }
  if (index == 0) {
    return pop_front();
  }
  if (index == size() - 1) {
    return pop_back();
  }
  auto current = head;
  for (auto i = 0u; i < index; i++) {
    current = current->next();
  }
  auto data = current->data();
  current->next()->prev(current->prev());
  current->prev()->next(current->next());
  size_--;
  delete current;
  return data;
}

template<typename T>
T structures::DoublyCircularList<T>::pop_back() {
  if (empty()) {
      throw std::out_of_range("Lista vazia");
  }
  if (size() == 1) {
    auto aux = head;
    auto data = aux->data();
    delete aux;
    head = nullptr;
    size_--;
    return data;
  }
  auto current = head->prev();
  auto data = current->data();
  current->prev()->next(head);
  head->prev(current->prev());
  size_--;
  delete current;
  return data;
}

template<typename T>
T structures::DoublyCircularList<T>::pop_front() {
  if (empty()) {
    throw std::out_of_range("Lista vazia");
  }
  if (size() == 1) {
    auto data = head->data();
    delete head;
    size_--;
    head = nullptr;
    return data;
  }
  auto data = head->data();
  auto prev_head = head;
  head->next()->prev(head->prev());
  head->prev()->next(head->next());
  head = head->next();
  size_--;
  delete prev_head;
  return data;
}

template<typename T>
void structures::DoublyCircularList<T>::remove(const T& data) {
  auto current = head;
  for (auto i = 0u; i < size(); i++) {
    if (data == current->data()) {
      pop(i);
      return;
    }
    current = current->next();
  }
}

template<typename T>
bool structures::DoublyCircularList<T>::empty() const {
  return size_ == 0;
}

template<typename T>
bool structures::DoublyCircularList<T>::contains(const T& data) const {
  auto current = head;
  for (auto i = 0u; i < size(); i++) {
    if (data == current->data()) {
      return true;
    }
    current = current->next();
  }
  return false;
}

template<typename T>
std::size_t structures::DoublyCircularList<T>::find(const T& data) const {
  auto current = head;
  for (auto i = 0u; i < size(); i++) {
    if (data == current->data()) {
      return i;
    }
    current = current->next();
  }
  return size();
}

template<typename T>
std::size_t structures::DoublyCircularList<T>::size() const {
  return size_;
}

#endif
