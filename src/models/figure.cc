#include "figure.h"

#include "viewer_widget.h"

namespace s21 {

QMatrix4x4 operator*(const QMatrix4x4 &qmat, s21::MVPMatrix &mvpmat) {
  QMatrix4x4 newmvp;
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      newmvp(i, j) = mvpmat.GetMVPMatrix()(i, j);
    }
  }
  return qmat * newmvp;
}

Figure::Figure(std::string path, ParserController &parser, ViewerWidget &widget)
    : widget_(widget) {
  parser.Parse(path);
  Q_ASSERT(vertices_buffer_.create() == true);
  Q_ASSERT(indices_buffer_.create() == true);
  AllocateIndexBuffer(parser.GetEdges().data(), parser.GetEdges().size());
  AllocateVertexBuffer(parser.GetVertices().data(),
                       parser.GetVertices().size());
}

void Figure::AllocateIndexBuffer(int *indices, size_t count) {
  Q_ASSERT(indices_buffer_.bind() == true);
  indices_buffer_.allocate(indices, count * sizeof(int));
  count_edges_ = count;
}

void Figure::AllocateVertexBuffer(float *vertices, size_t count) {
  Q_ASSERT(vertices_buffer_.bind() == true);
  vertices_buffer_.allocate(vertices, count * sizeof(float));
  count_vertices_ = count;
}

Figure::~Figure() {
  vertices_buffer_.destroy();
  indices_buffer_.destroy();
}

void Figure::BindData() {
  BindMVPBuffer();
  BindIndexBuffer();
  BindVertexBuffer();
}

void Figure::BindIndexBuffer() { Q_ASSERT(indices_buffer_.bind() == true); }

void Figure::BindVertexBuffer() {
  Q_ASSERT(vertices_buffer_.bind() == true);
  int vertexLocation = widget_.shaders_.attributeLocation("a_position");
  Q_ASSERT(vertexLocation != -1);
  widget_.shaders_.enableAttributeArray(vertexLocation);
  widget_.shaders_.setAttributeBuffer(vertexLocation, GL_FLOAT, 0, 3,
                                      sizeof(float) * 3);
}

void Figure::BindMVPBuffer() {
  widget_.shaders_.setUniformValue(
      "mvp_matrix", widget_.projection_ * mvpmatrix);
}

void Figure::Draw() {
  widget_.glDrawElements(GL_POINTS, count_edges_, GL_UNSIGNED_INT, nullptr);
  widget_.glDrawElements(GL_LINES, count_edges_, GL_UNSIGNED_INT, nullptr);
}
}  // namespace s21
