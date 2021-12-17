//! Copyright [2021] Gabriel de Vargas Coelho
#ifndef ANALIZE_XML
#define ANALIZE_XML

#include <string>
#include <fstream>
#include <exception>
#include "linked_stack.h"

//! Erro de XML mal formado
struct MalformadException : public std::exception
{
	const char* what () const throw () {
    return "Malformed xml";
  }
};

//! Classe analisadora de sintaxe xml
class AnalizeXML {
 public:
 //! Construtor
 /*!
  \param filename um std::string representando nome do arquivo
 */
  AnalizeXML(std::string& filename):
    filename_{filename}
  {}
  //! Inicializa a análise
  void analize() {
    read_file_by_lines();
  }
  //! Testa se arquivo é bem formado
  bool is_good() {
    if (formatted_ && stack_.size() == 0) {
      return true;
    }
    return false;
  }
  
 private:
  //! Lê arquivo por linhas
  void read_file_by_lines() {
    std::string line;
    std::ifstream myfile (filename_);
    while (getline(myfile, line)) {
      get_xml_tags_from_line(line);
    }

    myfile.close();
  }
  //! Identifica tags de uma linha do arquivo
  /*!
    \param line um std::string representado uma linha do arquivo 
  */
  void get_xml_tags_from_line(std::string& line) {
    if (line.size() == 0) {
      return;
    }
    while (line.find("<") != std::string::npos) {
      auto open_tag_index = line.find("<");
      auto close_tag_index = line.find(">");
      auto tag_size = close_tag_index - 1 - open_tag_index;
      auto tag = line.substr(open_tag_index + 1, tag_size);

      line.replace(open_tag_index, 1, "#");
      line.replace(close_tag_index, 1, "#");

      try {
        handle_stack(tag);
      } catch (MalformadException& e) {
        formatted_ = false;
        break;
      }
    }
  }
  //! Lida com a pilha
  /*!
    \param tag um std::string representando uma tag xml sem <>
  */
  void handle_stack(std::string& tag) {
    if (tag.compare(0, 1, "/") != 0) {
      stack_.push(tag);
      return;
    }
    auto tag_stack_top = stack_.top();
    if (tag.compare(1, tag.size(), tag_stack_top) != 0) {
      throw MalformadException();
    }
    stack_.pop();
  }

  std::string filename_;
  structures::LinkedStack<std::string> stack_;
  bool formatted_{true};
};

#endif