//! Copyright [2021] Gabriel de Vargas Coelho
#ifndef STRUCTURES_LINKED_LIST_H
#define STRUCTURES_LINKED_LIST_H

#include <cstdint>

namespace structures {

//! Classe lista encadeada
template<typename T>
class LinkedList {
 public:
    //! Construtor
    LinkedList();  // construtor padrão
    //! Destrutor
    ~LinkedList();  // destrutor
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
    //! Acessa na posição
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
    //! Elemento
    class Node {  // Elemento
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
        //! Acessa data
        T& data() {  // getter: data
            return data_;
        }
        //! Acessa data const
        const T& data() const {  // getter const: data
            return data_;
        }
        //! Acessa próximo elemento
        Node* next() {  // getter: próximo
            return next_;
        }
        //! Acessa próximo elemento const
        const Node* next() const {  // getter const: próximo
            return next_;
        }
        //! Atribui próximo elemento
        void next(Node* node) {  // setter: próximo
            next_ = node;
        }

     private:
        //! data
        T data_;
        //! Próximo elemento
        Node* next_{nullptr};
    };
    //! Último elemento da lista
    Node* end() {  // último nodo da lista
        auto it = head;
        for (auto i = 1u; i < size(); ++i) {
            it = it->next();
        }
        return it;
    }
    //! Primeiro elemento da lista
    Node* head{nullptr};
    //! Tamanho da lista
    std::size_t size_{0u};
};

}  // namespace structures

template<typename T>
structures::LinkedList<T>::LinkedList() {
    size_ = 0;
    head = nullptr;
}

template<typename T>
structures::LinkedList<T>::~LinkedList() {
    clear();
}

template<typename T>
void structures::LinkedList<T>::clear() {
    Node* current = head;
    while (current != nullptr) {
        auto next = current->next();
        delete current;
        current = next;
    }
    head = nullptr;
    size_ = 0;
}

template<typename T>
void structures::LinkedList<T>::push_back(const T& data) {
    Node* element = new Node(data);
    if (element == nullptr) {
        throw std::out_of_range("Lista cheia");
    }
    if (size() == 0) {
        head = element;
        size_++;
    } else {
        auto last = end();
        last->next(element);
        size_ += 1;
    }
}

template<typename T>
void structures::LinkedList<T>::push_front(const T& data) {
    Node* element = new Node(data, head);
    if (element == nullptr) {
        throw std::out_of_range("Lista cheia");
    }
    head = element;
    size_ += 1;
}

template<typename T>
void structures::LinkedList<T>::insert(const T& data, std::size_t index) {
    if (index > size()) {
        throw std::out_of_range("Índice fora do limite");
    }
    if (index == 0) {
        return push_front(data);
    }
    Node* element = new Node(data);
    if (element == nullptr) {
        throw std::out_of_range("Lista cheia");
    }
    auto pos = 0u;
    auto previous = head;
    while (pos < index - 1) {
        previous = previous->next();
        pos++;
    }
    element->next(previous->next());
    previous->next(element);
    size_++;
}

template<typename T>
void structures::LinkedList<T>::insert_sorted(const T& data) {
    Node* element = new Node(data);
    if (element == nullptr) {
        throw std::out_of_range("Lista cheia");
    }
    if (size() == 0) {
        return push_front(data);
    }
    auto current = head;
    auto pos = 0u;
    while (current->next() != nullptr && data > current->data()) {
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
T& structures::LinkedList<T>::at(std::size_t index) {
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
T structures::LinkedList<T>::pop(std::size_t index) {
    if (empty()) {
        throw std::out_of_range("Lista vazia");
    }
    if (index > size() - 1) {
        throw std::out_of_range("Índice fora do limite");
    }
    if (index == 0) {
        return pop_front();
    }
    auto previous = head;
    for (auto i = 1u; i < index; i++) {
        previous = previous->next();
    }
    auto exclude = previous->next();
    auto data = exclude->data();
    previous->next(exclude->next());
    size_--;
    delete exclude;
    return data;
}

template<typename T>
T structures::LinkedList<T>::pop_back() {
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
    auto previous = head;
    for (auto i = 1u; i < size() - 1; i++) {
        previous = previous->next();
    }
    auto exclude = previous->next();
    auto data = exclude->data();
    previous->next(nullptr);
    size_--;
    delete exclude;
    return data;
}

template<typename T>
T structures::LinkedList<T>::pop_front() {
    if (empty()) {
        throw std::out_of_range("Lista vazia");
    }
    auto previous_head = head;
    auto data = previous_head->data();
    head = previous_head->next();
    size_--;
    delete previous_head;
    return data;
}

template<typename T>
void structures::LinkedList<T>::remove(const T& data) {
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
bool structures::LinkedList<T>::empty() const {
    return size_ == 0;
}

template<typename T>
bool structures::LinkedList<T>::contains(const T& data) const {
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
std::size_t structures::LinkedList<T>::find(const T& data) const {
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
std::size_t structures::LinkedList<T>::size() const {
    return size_;
}

#endif
