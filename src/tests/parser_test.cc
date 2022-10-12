#include <gtest/gtest.h>

#include "parser_controller.h"

TEST(parser, test1) {
  s21::Parser P;
  P.Parse("../objs/cube.obj");
  ASSERT_EQ(P.GetVertices().size(), 24);
  ASSERT_EQ(P.GetEdges().size(), 24);

  std::unique_ptr<s21::ParserController> transmitter_;
  transmitter_ = std::make_unique<s21::ParserController>();
  transmitter_->Parse("../objs/cube.obj");
  ASSERT_EQ(transmitter_->GetVertices().size(), 24);
  ASSERT_EQ(transmitter_->GetEdges().size(), 24);
}
