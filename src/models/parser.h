#ifndef SRC_MODELS_PARSER_H_
#define SRC_MODELS_PARSER_H_

#include <fstream>
#include <sstream>
#include <string>
#include <vector>

namespace s21 {
class Parser {
 public:
  void Parse(std::string path);

  std::vector<float> GetVertices() const { return vertices_; }
  std::vector<int> GetEdges() const { return edges_; }
  void Clear();

 private:
  std::vector<float> vertices_ = {};
  std::vector<int> edges_ = {};

  void ScanVertices(std::string line);
  void ScanEdge(std::string line);
};
}  // namespace s21

#endif  // SRC_MODELS_PARSER_H_
