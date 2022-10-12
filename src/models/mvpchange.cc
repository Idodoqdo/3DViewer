#include "mvpchange.h"
namespace s21 {
void MVPMatrix::RotateX(float angleX) {
  mat_rotX(1, 1) = cos(angleX);
  mat_rotX(2, 2) = cos(angleX);
  mat_rotX(1, 2) = -sin(angleX);
  mat_rotX(2, 1) = sin(angleX);
  Tranform();
}

void MVPMatrix::RotateY(float angleY) {
  mat_rotY(0, 0) = cos(angleY);
  mat_rotY(2, 2) = cos(angleY);
  mat_rotY(2, 0) = -sin(angleY);
  mat_rotY(0, 2) = sin(angleY);
  Tranform();
}

void MVPMatrix::RotateZ(float angleZ) {
  mat_rotZ(0, 0) = cos(angleZ);
  mat_rotZ(1, 1) = cos(angleZ);
  mat_rotZ(0, 1) = -sin(angleZ);
  mat_rotZ(1, 0) = sin(angleZ);
  Tranform();
}

void MVPMatrix::SetIdentity(s21::S21Matrix& matrix) {
  for (unsigned int i = 0; i < static_cast<unsigned int>(matrix.getRows());
       ++i) {
    for (unsigned int j = 0; j < static_cast<unsigned int>(matrix.getColumns());
         ++j) {
      i == j ? matrix(i, j) = 1 : matrix(i, j) = 0;
    }
  }
}

void MVPMatrix::TranslateX(float shiftX) {
  matrix(0, 3) = position[0] = shiftX;
}

void MVPMatrix::TranslateY(float shiftY) {
  matrix(1, 3) = position[1] = shiftY;
}

void MVPMatrix::TranslateZ(float shiftZ) {
  matrix(2, 3) = position[2] = shiftZ;
}

void MVPMatrix::Scale(float scale_factor) {
  for (unsigned int i = 0;
       i <= static_cast<unsigned int>(matrix.getColumns() - 1); ++i) {
    mat_scale(i, i) = scale_factor;
  }
  mat_scale(3, 3) = 1;
  Tranform();
}

void MVPMatrix::Tranform() {
  SetPosition();
  matrix *= mat_rotX * mat_rotY * mat_rotZ * mat_scale;
}

void MVPMatrix::SetPosition() {
  SetIdentity(matrix);
  matrix(0, 3) = position[0];
  matrix(1, 3) = position[1];
  matrix(2, 3) = position[2];
}
}  // namespace s21
