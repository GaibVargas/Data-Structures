//! Copyright [2021] Gabriel de Vargas Coelho

namespace structures {

//! Classe fila encadeada
template<typename T>
class LinkedQueue {
 public:
  //! Construtor
  LinkedQueue();
  //! Destrutor
  ~LinkedQueue();
  //! Limpa fila
  void clear();
  //! Enfileirar
  void enqueue(const T& data);
  //! Desenfileirar
  T dequeue();
  //! Início da fila
  T& front() const;
  //! Fim da fila
  T& back() const;
  //! Verifica fila vazia
  bool empty() const;
  //! Tamanho da fila
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
  //! Início da fila
  Node* head;
  //! Fim da fila
  Node* tail;
  //! Tamanho
  std::size_t size_;
};

}  //  namespace structures

template<typename T>
structures::LinkedQueue<T>::LinkedQueue() {
  head = nullptr;
  tail = nullptr;
  size_ = 0;
}

template<typename T>
structures::LinkedQueue<T>::~LinkedQueue() {
  clear();
}

template<typename T>
void structures::LinkedQueue<T>::clear() {
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
void structures::LinkedQueue<T>::enqueue(const T& data) {
  Node* element = new Node(data);
  if (element == nullptr) {
    throw std::out_of_range("Fila cheia");
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
T structures::LinkedQueue<T>::dequeue() {
  if (empty()) {
    throw std::out_of_range("Fila vazia");
  }
  auto current_head = head;
  auto data = current_head->data();
  head = current_head->next();
  if (size() == 1) {
    tail = nullptr;
  }
  delete current_head;
  size_--;
  return data;
}

template<typename T>
T& structures::LinkedQueue<T>::front() const {
  if (empty()) {
    throw std::out_of_range("Fila vazia");
  }
  return head->data();
}

template<typename T>
T& structures::LinkedQueue<T>::back() const {
  if (empty()) {
    throw std::out_of_range("Fila vazia");
  }
  return tail->data();
}

template<typename T>
bool structures::LinkedQueue<T>::empty() const {
  return size_ == 0;
}

template<typename T>
std::size_t structures::LinkedQueue<T>::size() const {
  return size_;
}
