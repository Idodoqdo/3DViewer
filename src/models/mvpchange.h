#ifndef SRC_MODELS_MVPMATRIX_H_
#define SRC_MODELS_MVPMATRIX_H_
#include <math.h>

#include <vector>

#include "s21_matrix_oop.h"

namespace s21 {
class MVPMatrix {
 public:
  MVPMatrix() {
    SetIdentity(matrix);
    SetIdentity(mat_rotX);
    SetIdentity(mat_rotY);
    SetIdentity(mat_rotZ);
    SetIdentity(mat_scale);
  };
  void RotateX(float angleX);
  void RotateY(float angleY);
  void RotateZ(float angleZ);
  void TranslateX(float shiftX);
  void TranslateY(float shiftY);
  void TranslateZ(float shiftZ);
  void Scale(float scale_factor);
  void Tranform();
  s21::S21Matrix GetMVPMatrix() { return matrix; };

 private:
  s21::S21Matrix matrix, mat_rotX, mat_rotY, mat_rotZ, mat_scale;
  void SetPosition();
  void SetIdentity(s21::S21Matrix& matrix);
  std::vector<float> position{0, 0, 0};
};
}  // namespace s21

#endif  // SRC_MODELS_MVPMATRIX_H_
