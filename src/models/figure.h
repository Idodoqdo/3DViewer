#ifndef SRC_MODELS_FIGURE_H_
#define SRC_MODELS_FIGURE_H_
#include <QOpenGLBuffer>
#include <QVector3D>
#include <iostream>
#include <string>

#include "mvpchange.h"
#include "parser_controller.h"

class ViewerWidget;

namespace s21 {
class Figure {
 public:
  Figure(std::string path, ParserController &parser, ViewerWidget &widget);
  Figure() = delete;
  ~Figure();
  void Draw();
  void BindData();

  size_t GetEdgesCount() const { return count_edges_ / 2; }
  size_t GetVerticesCount() const { return count_vertices_ / 3; }
  void AllocateIndexBuffer(int *indices, size_t count);
  void AllocateVertexBuffer(float *vertices, size_t count);
  void BindIndexBuffer();
  void BindVertexBuffer();
  void BindMVPBuffer();
  QOpenGLBuffer vertices_buffer_{};
  QOpenGLBuffer indices_buffer_{QOpenGLBuffer::IndexBuffer};
  void TranslateX(float shiftX) { mvpmatrix.TranslateX(shiftX); }
  void TranslateY(float shiftY) { mvpmatrix.TranslateY(shiftY); }
  void TranslateZ(float shiftZ) { mvpmatrix.TranslateZ(shiftZ); }
  void RotateX(float rotationX) { mvpmatrix.RotateX(rotationX); }
  void RotateY(float rotationY) { mvpmatrix.RotateY(rotationY); }
  void RotateZ(float rotationZ) { mvpmatrix.RotateZ(rotationZ); }
  void Scale(float scale) { mvpmatrix.Scale(scale); }

 private:
  size_t count_edges_;
  size_t count_vertices_;
  MVPMatrix mvpmatrix;
  ViewerWidget &widget_;
};

QMatrix4x4 operator*(const QMatrix4x4 &qmat, s21::MVPMatrix &mvpmat);
}  // namespace s21

#endif  // SRC_MODELS_FIGURE_H_
