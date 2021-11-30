#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "linked_queue.h"
#include "analizeXML.cpp"

struct Point {
  int x;
  int y;
};

int related_pixels(int** matriz, int height, int width) {
  structures::LinkedQueue<Point> queue;
  int label = 1;
  int** image = new int*[height];

  for (auto i = 0; i < height; ++i) {
    image[i] = new int[width];
  }
  
  for (auto i = 0; i < height; ++i) {
    for (auto j = 0; j < width; ++j) {
      if (matriz[i][j] == 1 && image[i][j] == 0) {
        queue.enqueue(Point{j, i});
        image[i][j] = label;
      
        while (!queue.empty()) {
          auto point = queue.dequeue();
          // Verifica direita
          if (point.x + 1 < width && matriz[point.y][point.x + 1] == 1 && image[point.y][point.x + 1] == 0) {
            queue.enqueue(Point{point.x + 1, point.y});
            image[point.y][point.x + 1] = label;
          }
          // Verifica esquerda
          if (point.x - 1 >= 0 && matriz[point.y][point.x - 1] == 1 && image[point.y][point.x - 1] == 0) {
            queue.enqueue(Point{point.x - 1, point.y});
            image[point.y][point.x - 1] = label;
          }
          // Verifica acima
          if (point.y + 1 < height && matriz[point.y + 1][point.x] == 1 && image[point.y + 1][point.x] == 0) {
            queue.enqueue(Point{point.x, point.y + 1});
            image[point.y + 1][point.x] = label;
          }
          // Verifica abaixo
          if (point.y - 1 >= 0 && matriz[point.y - 1][point.x] == 1 && image[point.y - 1][point.x] == 0) {
            queue.enqueue(Point{point.x, point.y - 1});
            image[point.y - 1][point.x] = label;
          }
        }

        label++;
      }
    }
  }

  return label - 1;
}

bool has_tag(std::string const& tag, std::string& line) {
  return line.find(tag) != std::string::npos;
}

std::string get_value_between_tag(std::string const& tag, std::string& line) {
  auto close_tag = tag.substr();
  close_tag.insert(1, "/");
  int open_tag_index = line.find(tag);
  int close_tag_index = line.find(close_tag);
  int open_tag_last_position = open_tag_index + tag.size();
  auto value = line.substr(open_tag_last_position, close_tag_index - open_tag_last_position);
  return value;
}

void read_file(std::string& filename) {
  int index = 0;
  int** matriz;
  std::string line, name, height, width;
  int height_number, width_number;
  bool open_data, close_data = false;
  std::ifstream myfile (filename);
  while (getline(myfile, line)) {
    if (has_tag("<name>", line)) {
      name = get_value_between_tag("<name>", line);
    }
    if (has_tag("<height>", line)) {
      height = get_value_between_tag("<height>", line);
      height_number = std::stoi(height);
      matriz = new int*[height_number];
    }
    if (has_tag("<width>", line)) {
      width = get_value_between_tag("<width>", line);
      width_number = std::stoi(width);
    }
    if (open_data && !close_data) {
      if (!has_tag("</data>", line)) {
        auto number_array = new int[width_number];
        for (auto i = 0; i < width_number; ++i) {
          int bit;
          std::stringstream stream;
          stream << line[i];
          stream >> bit;
          number_array[i] = bit;
        }
        matriz[index] = number_array;
        index++;
      }
    }
    if (has_tag("<data>", line)) {
      open_data = true;
      close_data = false;
    }
    if (has_tag("</data>", line)) {
      close_data = true;
      open_data = false;
    }
    if (!has_tag("</data>", line)) {
      close_data = false;
    }
    if (close_data) {
      auto related = related_pixels(matriz, height_number, width_number);
      std::cout << name << " " << related << std::endl;
      index = 0;
    }
  }

  myfile.close();
}

int main() {
  std::string xmlfilename;

  std::cin >> xmlfilename;

  auto analizer = AnalizeXML(xmlfilename);

  analizer.analize();

  if (!analizer.is_good()) {
    std::cout << "error\n";
    return 0;
  }

  read_file(xmlfilename);

  return 0;
}
