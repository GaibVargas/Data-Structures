// Copyright [2019] <Gabriel de Vargas Coelho...>
#ifndef STRUCTURES_STRING_LIST_H
#define STRUCTURES_STRING_LIST_H

#include <cstdint>
#include <stdexcept>  // C++ exceptions
#include <cstring>

namespace structures {

template<typename T>
//! Classe Lista em vetor
class ArrayList {
 public:
  //! construtor simples
  ArrayList();
  //! construtor parametrizado
  explicit ArrayList(std::size_t max_size);
  //! destrutor
  ~ArrayList();
  //! limpa lista
  void clear();
  //! adiciona ao final
  void push_back(const T& data);
  //! adiciona à frente
  void push_front(const T& data);
  //! adiciona na posição
  void insert(const T& data, std::size_t index);
  //! adiciona em ordem
  void insert_sorted(const T& data);
  //! retira da posição
  T pop(std::size_t index);
  //! retira do final
  T pop_back();
  //! retira da frente
  T pop_front();
  //! retira dado específico
  void remove(const T& data);
  //! verifica se está cheia
  bool full() const;
  //! verifica se está vazia
  bool empty() const;
  //! verifica se contem elemento
  bool contains(const T& data) const;
  //! encontra elemento
  std::size_t find(const T& data) const;
  //! retorna tamanho
  std::size_t size() const;
  //! retorna tamanho máximo
  std::size_t max_size() const;
  //! retorna elemento da posição com verificação
  T& at(std::size_t index);
  //! retorna elemento da posição
  T& operator[](std::size_t index);
  //! retorna elemento da posição com verificação
  const T& at(std::size_t index) const;
  //! retorna elemento da posição com verificação
  const T& operator[](std::size_t index) const;

 protected:
  //! vetor base
  T* contents;
  //! verifica sucessor
  bool successor(const T& data1, const T& data2);
  //! tamanho
  std::size_t size_;
  //! tamanho máximo
  std::size_t max_size_;

 private:
  //! tamanho default
  static const auto DEFAULT_MAX = 10u;
};

//! ArrayListString é uma especializacao da classe ArrayList
class ArrayListString : public ArrayList<char *> {
 public:
  //! Construtor
  ArrayListString() : ArrayList() {}
  //! Construtor explicito
  explicit ArrayListString(std::size_t max_size) : ArrayList(max_size) {}
  //! Destrutor
  ~ArrayListString();
  //! Limpa lista
  void clear();
  //! Adiciona ao final
  void push_back(const char *data);
  //! Adiciona à frente
  void push_front(const char *data);
  //! Adiciona na posição
  void insert(const char *data, std::size_t index);
  //! Adiciona ordenadamente
  void insert_sorted(const char *data);
  //! Retira da posição
  char *pop(std::size_t index);
  //! Retira do final
  char *pop_back();
  //! Retira da frente
  char *pop_front();
  //! Retira dado
  void remove(const char *data);
  //! Verifica se contém dado
  bool contains(const char *data);
  //! Retorna índice do dado
  std::size_t find(const char *data);
};

}  // namespace structures

template<typename T>
structures::ArrayList<T>::ArrayList(std::size_t max_size) {
  size_ = 0;
  max_size_ = max_size;
  contents = new T[max_size];
}

template<typename T>
structures::ArrayList<T>::ArrayList() {
  ArrayList(std::size_t(DEFAULT_MAX));
}

template<typename T>
structures::ArrayList<T>::~ArrayList() {
  delete[] contents;
}

template<typename T>
void structures::ArrayList<T>::clear() {
  size_ = 0;
}

template<typename T>
void structures::ArrayList<T>::push_back(const T& data) {
  if (full()) {
    throw std::out_of_range("Lista cheia");
  }
  size_ += 1;
  contents[size_ - 1] = data;
}

template<typename T>
void structures::ArrayList<T>::push_front(const T& data) {
  if (full()) {
    throw std::out_of_range("Lista cheia");
  }
  size_ += 1;
  for (auto i = size() - 1; i >= 1; i--) {
    contents[i] = contents[i - 1];
  }
  contents[0] = data;
}

template<typename T>
void structures::ArrayList<T>::insert(const T& data, std::size_t index) {
  if (full()) {
    throw std::out_of_range("Lista cheia");
  }
  if (index > size()) {
    throw std::out_of_range("Index Out of Range");
  }
  for (auto i = size(); i > index; i--) {
    contents[i] = contents[i - 1];
  }
  size_ += 1;
  contents[index] = data;
}

template<typename T>
void structures::ArrayList<T>::insert_sorted(const T& data) {
  if (full()) {
    throw std::out_of_range("Lista cheia");
  }
  std::size_t pos = 0;
  while (pos < size_ && successor(data, contents[pos])) {
    pos += 1;
  }
  insert(data, pos);
}

template<typename T>
T structures::ArrayList<T>::pop(std::size_t index) {
  if (index >= size() || index < 0) {
    throw std::out_of_range("Index Out Of Range");
  }
  size_ -= 1;
  auto data = contents[index];
  for (auto i = index; i < size(); i++) {
    contents[i] = contents[i + 1];
  }
  return data;
}

template<typename T>
T structures::ArrayList<T>::pop_back() {
  if (empty()) {
    throw std::out_of_range("Lista vazia");
  }
  size_ -= 1;
  return contents[size()];
}

template<typename T>
T structures::ArrayList<T>::pop_front() {
  if (empty()) {
    throw std::out_of_range("Lista vazia");
  }
  size_ -= 1;
  auto data = contents[0];
  for (auto i = 0u; i < size(); i++) {
    contents[i] = contents[i + 1];
  }
  return data;
}

template<typename T>
void structures::ArrayList<T>::remove(const T& data) {
  auto index = find(data);
  pop(index);
}

template<typename T>
bool structures::ArrayList<T>::full() const {
  return size_ == max_size_;
}

template<typename T>
bool structures::ArrayList<T>::empty() const {
  return size() == 0u;
}

template<typename T>
bool structures::ArrayList<T>::contains(const T& data) const {
  auto contain = false;
  for (auto i = 0u; i < size(); i++) {
    if (contents[i] == data) {
      contain = true;
      break;
    }
  }
  return contain;
}

template<typename T>
std::size_t structures::ArrayList<T>::find(const T& data) const {
  auto index = size();
  for (auto i = 0u; i < size(); i++) {
    if (contents[i] == data) {
      index = i;
      break;
    }
  }
  return index;
}

template<typename T>
std::size_t structures::ArrayList<T>::size() const {
  return size_;
}

template<typename T>
std::size_t structures::ArrayList<T>::max_size() const {
  return max_size_;
}

template<typename T>
T& structures::ArrayList<T>::at(std::size_t index) {
  if (index >= size() || index < 0) {
    throw std::out_of_range("Index Out Of Range");
  }
  return contents[index];
}

template<typename T>
const T& structures::ArrayList<T>::at(std::size_t index) const {
  if (index >= size() || index < 0) {
    throw std::out_of_range("Index Out Of Range");
  }
  return contents[index];
}

template<typename T>
T& structures::ArrayList<T>::operator[](std::size_t index) {
  return contents[index];
}

template<typename T>
const T& structures::ArrayList<T>::operator[](std::size_t index) const {
  return contents[index];
}

template<typename T>
bool structures::ArrayList<T>::successor(const T& data1, const T& data2) {
  return data1 > data2;
}

structures::ArrayListString::~ArrayListString() {
  clear();
}

void structures::ArrayListString::clear() {
  for (auto i = 0u; i < size(); i++) {
    delete[] contents[i];
  }
  size_ = 0;
}

void structures::ArrayListString::push_back(const char* data) {
  if (full()) {
    throw std::out_of_range("Lista cheia");
  }
  char *datanew = new char[strlen(data)+1];
  if (datanew == nullptr) {
    throw std::out_of_range("Lista cheia");
  }
  snprintf(datanew, strlen(data)+1, "%s", data);
  contents[size_] = datanew;
  size_ += 1;
}

void structures::ArrayListString::push_front(const char *data) {
  if (full()) {
    throw std::out_of_range("Lista cheia");
  }
  char *datanew = new char[strlen(data)+1];
  if (datanew == nullptr) {
    throw std::out_of_range("Lista cheia");
  }
  snprintf(datanew, strlen(data)+1, "%s", data);
  size_ += 1;
  for (auto i = size() - 1; i >= 1; i--) {
    contents[i] = contents[i - 1];
  }
  contents[0] = datanew;
}

void structures::ArrayListString::insert(const char *data, std::size_t index) {
  if (full()) {
    throw std::out_of_range("Lista cheia");
  }
  if (index > size()) {
    throw std::out_of_range("Index Out of Range");
  }
  char *datanew = new char[strlen(data)+1];
  if (datanew == nullptr) {
    throw std::out_of_range("Lista cheia");
  }
  snprintf(datanew, strlen(data)+1, "%s", data);
  for (auto i = size(); i > index; i--) {
    contents[i] = contents[i - 1];
  }
  contents[index] = datanew;
  size_ += 1;
}

void structures::ArrayListString::insert_sorted(const char *data) {
  if (full()) {
    throw std::out_of_range("Lista cheia");
  }
  char *datanew = new char[strlen(data)+1];
  if (datanew == nullptr) {
    throw std::out_of_range("Lista cheia");
  }
  snprintf(datanew, strlen(data)+1, "%s", data);
  std::size_t pos = 0;
  while (pos < size_ && strcmp(datanew, contents[pos]) > 0) {
    pos += 1;
  }
  insert(data, pos);
}

char* structures::ArrayListString::pop(std::size_t index) {
  if (empty()) {
    throw std::out_of_range("Lista vazia");
  }
  if (index >= size()) {
    throw std::out_of_range("Índice fora do limite");
  }
  auto data = contents[index];
  for (auto i = index; i < size() - 1; i++) {
    contents[i] = contents[i + 1];
  }
  size_ -= 1;
  return data;
}

char* structures::ArrayListString::pop_back() {
  if (empty()) {
    throw std::out_of_range("Lista vazia");
  }
  size_ -= 1;
  return contents[size()];
}

char* structures::ArrayListString::pop_front() {
  if (empty()) {
    throw std::out_of_range("Lista vazia");
  }
  auto data = contents[0];
  for (auto i = 1u; i < size(); i++) {
    contents[i - 1] = contents[i];
  }
  size_ -= 1;
  return data;
}

void structures::ArrayListString::remove(const char *data) {
  if (empty()) {
    throw std::out_of_range("Lista vazia");
  }
  auto index = find(data);
  pop(index);
}

bool structures::ArrayListString::contains(const char *data) {
  auto contain = false;
  for (auto i = 0u; i < size(); i++) {
    if (strcmp(contents[i], data) == 0) {
      contain = true;
      break;
    }
  }
  return contain;
}

std::size_t structures::ArrayListString::find(const char *data) {
  auto index = size();
  for (auto i = 0u; i < size(); i++) {
    if (strcmp(contents[i], data) == 0) {
      index = i;
      break;
    }
  }
  return index;
}

#endif
