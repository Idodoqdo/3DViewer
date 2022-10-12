#include "parser.h"

namespace s21 {
void Parser::Parse(std::string path) {
  std::ifstream file(path);  // файл из которого читаем
  if (!file.is_open())       // если не удалось открыть
    throw std::runtime_error("The file does not exist.");
  std::string line = {};  // считанные строки
  while (std::getline(file, line)) {  // очередную строку в переменную (line)
    if (line.size() > 2) {
      if (line.at(0) == 'v' && line.at(1) == ' ') {  //  если вершины
        ScanVertices(line);
      } else if (line.at(0) == 'f' && line.at(1) == ' ') {
        ScanEdge(line);  //  многоугольник разобрать на рёбра
      }
    }
  }
  file.close();  // закрываем файл
}

void Parser::Clear() {
  vertices_.clear();
  vertices_.shrink_to_fit();
  edges_.clear();
  edges_.shrink_to_fit();
}

void Parser::ScanVertices(std::string line) {
  float x = 0, y = 0, z = 0;
  sscanf(line.c_str(), "v %f %f %f", &x, &y, &z);
  vertices_.push_back(x);
  vertices_.push_back(y);
  vertices_.push_back(z);
}

void Parser::ScanEdge(std::string line) {
  int count = 0;  //  счётчик вершин многоугольника
  int first_vet = 0;  //  Первая вершина многоугольника
  int last_vet = 0;  //  Последняя вершина многоугольника
  std::istringstream iss(line);
  for (std::string token; std::getline(iss, token, ' ');) {
    int ind_tmp = 0;  //  Текущая вершина
    if (sscanf(token.c_str(), "%d", &ind_tmp) == 1) {
      if (count == 0) {
        first_vet = ind_tmp - 1;
        edges_.push_back(first_vet);
        count = 1;
      } else if (count == 1) {
        last_vet = ind_tmp - 1;
        edges_.push_back(last_vet);
        count = 2;
      } else if (count >= 2) {
        edges_.push_back(last_vet);
        last_vet = ind_tmp - 1;
        edges_.push_back(last_vet);
        count = count + 2;
      }
    }
  }
  if (count > 2) {  //  Замыкающее ребро в многоугольник
    edges_.push_back(last_vet);
    edges_.push_back(first_vet);
  }
}
}  // namespace s21
