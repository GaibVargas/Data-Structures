//! Copyright [2021] Gabriel de Vargas Coelho

namespace structures {

//! Classe lista duplamente encadeada
template<typename T>
class DoublyLinkedList {
 public:
  //! Construtor
  DoublyLinkedList();
  //! Destrutor
  ~DoublyLinkedList();
  //! Limpa lista
  void clear();
  //! Adiciona ao final
  void push_back(const T& data);
  //! Adiciona no início
  void push_front(const T& data);
  //! Adiciona na posição
  void insert(const T& data, std::size_t index);
  //! Adiciona ordenadamente
  void insert_sorted(const T& data);
  //! Retira da posição
  T pop(std::size_t index);
  //! Retira do fim
  T pop_back();
  //! Retira do início
  T pop_front();
  //! Retira dado específico
  void remove(const T& data);
  //! Verifica se lista vazia
  bool empty() const;
  //! Verifica se contém
  bool contains(const T& data) const;
  //! Acessa elemento na posição, checando limites
  T& at(std::size_t index);
  //! Acessa elemento na posição, checando limites (const)
  const T& at(std::size_t index) const;
  //! Posição de um dado
  std::size_t find(const T& data) const;
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

  //! Primeiro da lista
  Node* head{nullptr};
  //! Último da lista
  Node* tail{nullptr};
  //! Tamanho
  std::size_t size_{0u};
};

}  //  namespace structures

template<typename T>
structures::DoublyLinkedList<T>::DoublyLinkedList() {
  size_ = 0;
  head = nullptr;
  tail = nullptr;
}

template<typename T>
structures::DoublyLinkedList<T>::~DoublyLinkedList() {
  clear();
}

template<typename T>
void structures::DoublyLinkedList<T>::clear() {
  Node* current = head;
  while (current != nullptr) {
    auto next = current->next();
    delete current;
    current = next;
  }
  head = nullptr;
  tail = nullptr;
  size_ = 0;
}

template<typename T>
void structures::DoublyLinkedList<T>::push_back(const T& data) {
  Node* element = new Node(data, tail, nullptr);
  if (element == nullptr) {
    throw std::out_of_range("Lista cheia");
  }
  if (size() == 0) {
    head = element;
  } else {
    tail->next(element);
  }
  tail = element;
  size_++;
}

template<typename T>
void structures::DoublyLinkedList<T>::push_front(const T& data) {
  Node* element = new Node(data, head);
  if (element == nullptr) {
    throw std::out_of_range("Lista cheia");
  }
  if (size() == 0) {
    tail = element;
  } else {
    head->prev(element);
  }
  head = element;
  size_++;
}

template<typename T>
void structures::DoublyLinkedList<T>::insert(const T& data, std::size_t index) {
  if (index > size()) {
    throw std::out_of_range("Índice fora dos limites");
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
  auto current = head;
  for (auto pos = 0u; pos < index; pos++) {
    current = current->next();
  }
  element->next(current);
  element->prev(current->prev());
  current->prev()->next(element);
  current->prev(element);
  size_++;
}

template<typename T>
void structures::DoublyLinkedList<T>::insert_sorted(const T& data) {
  if (size() == 0) {
    return push_front(data);
  }
  auto pos = 0u;
  auto current = head;
  while (current != nullptr && data > current->data()) {
    current = current->next();
    pos++;
  }
  return insert(data, pos);
}

template<typename T>
T structures::DoublyLinkedList<T>::pop_back() {
  if (empty()) {
    throw std::out_of_range("Lista vazia");
  }
  auto previous_tail = tail;
  auto data = previous_tail->data();
  if (size() != 1) {
    previous_tail->prev()->next(nullptr);
    tail = previous_tail->prev();
  } else {
    head = nullptr;
    tail = nullptr;
  }
  delete previous_tail;
  size_--;
  return data;
}

template<typename T>
T structures::DoublyLinkedList<T>::pop_front() {
  if (empty()) {
    throw std::out_of_range("Lista vazia");
  }
  if (size() == 1) {
    tail = nullptr;
  }
  auto data = head->data();
  auto previous_head = head;
  head = previous_head->next();
  if (head != nullptr) {
    head->prev(nullptr);
  }
  delete previous_head;
  size_--;
  return data;
}

template<typename T>
T structures::DoublyLinkedList<T>::pop(std::size_t index) {
  if (empty()) {
    throw std::out_of_range("Lista vazia");
  }
  if (index >= size()) {
    throw std::out_of_range("Índice fora dos limites");
  }
  if (index == 0) {
    return pop_front();
  }
  if (index == size() - 1) {
    return pop_back();
  }
  auto current = head;
  for (auto pos = 0u; pos < index; pos++) {
    current = current->next();
  }
  current->prev()->next(current->next());
  current->next()->prev(current->prev());
  auto data = current->data();
  delete current;
  size_--;
  return data;
}

template<typename T>
void structures::DoublyLinkedList<T>::remove(const T& data) {
  if (empty()) {
    throw std::out_of_range("Lista vazia");
  }
  auto pos = find(data);
  if (pos == size()) return;
  pop(pos);
}

template<typename T>
bool structures::DoublyLinkedList<T>::empty() const {
  return size_ == 0;
}

template<typename T>
bool structures::DoublyLinkedList<T>::contains(const T& data) const {
  auto current = head;
  while (current != nullptr) {
    if (current->data() == data) {
      return true;
    }
    current = current->next();
  }
  return false;
}

template<typename T>
T& structures::DoublyLinkedList<T>::at(std::size_t index) {
  if (index >= size()) {
    throw std::out_of_range("Índice fora dos limites");
  }
  auto current = head;
  for (auto pos = 0u; pos < index; pos++) {
    current = current->next();
  }
  return current->data();
}

template<typename T>
const T& structures::DoublyLinkedList<T>::at(std::size_t index) const {
  if (index >= size()) {
    throw std::out_of_range("Índice fora dos limites");
  }
  auto current = head;
  for (auto pos = 0u; pos < index; pos++) {
    current = current->next();
  }
  return current->data();
}

template<typename T>
std::size_t structures::DoublyLinkedList<T>::find(const T& data) const {
  auto current = head;
  auto pos = 0u;
  while (current != nullptr && current->data() != data) {
    current = current->next();
    pos++;
  }
  return pos;
}

template<typename T>
std::size_t structures::DoublyLinkedList<T>::size() const {
  return size_;
}
