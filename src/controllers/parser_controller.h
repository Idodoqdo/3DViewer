#ifndef SRC_CONTROLLERS_PARSER_CONTROLLER_H
#define SRC_CONTROLLERS_PARSER_CONTROLLER_H

#include <memory>

#include "parser.h"

namespace s21 {
class ParserController {
 public:
  ParserController() : parser_(std::make_unique<Parser>()) {}

  void Parse(std::string path) {
    parser_->Clear();
    parser_->Parse(path);
  }
  std::vector<float> GetVertices() const { return parser_->GetVertices(); }
  std::vector<int> GetEdges() const { return parser_->GetEdges(); }

 private:
  std::unique_ptr<Parser> parser_;
};
}  // namespace s21

#endif  // SRC_CONTROLLERS_PARSER_CONTROLLER_H
