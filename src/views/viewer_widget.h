// Copyright 2022 <lwolmer, jgerrick, lshiela>
#ifndef SRC_VIEWS_VIEWER_WIDGET_H_
#define SRC_VIEWS_VIEWER_WIDGET_H_

#include <math.h>
// #include "qgifimage.h"

#include <QBasicTimer>
#include <QColor>
#include <QDir>
#include <QFileDialog>
#include <QFileInfo>
#include <QMainWindow>
#include <QMatrix4x4>
#include <QOpenGLBuffer>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>
#include <QOpenGLWidget>
#include <QQuaternion>
#include <QTimer>
#include <QVector2D>
#include <vector>

#include "parser_controller.h"

#define LINES_BIND_LOC 4

namespace s21 {
class Figure;
}

class ViewerWidget : public QOpenGLWidget, protected QOpenGLFunctions {
  Q_OBJECT
  friend s21::Figure;

 public:
  ViewerWidget(QWidget *parent = nullptr,
               Qt::WindowFlags f = Qt::WindowFlags());
  ~ViewerWidget();
  void paintGL() override;
  void resizeGL(int w, int h) override;
  void drawCubeGeometry();
  void LoadModel(QString path);

  QColor GetBackgroundColor() { return background_color_; }
  QColor GetEdgesColor() { return edges_color_; }
  QColor GetVerticesColor() const { return vertices_color_; }

  int GetFigureEdgesCount(size_t index) const;
  int GetFigureVerticesCount(size_t index) const;
  int GetEdgesType() const { return edges_type_; }
  int GetVerticesType() const { return vertices_type_; }
  int GetProjectionType() const { return projection_type_; }
  float GetVerticesSize() const { return vertices_size_; }
  float GetEdgeThickness() const { return edges_thickness_; }

  void SetBackgroundColor(QColor color) { background_color_ = color; }
  void SetEdgesColor(QColor color) { edges_color_ = color; }
  void SetVerticesColor(QColor color) { vertices_color_ = color; }
  void SetEdgesType(int type) { edges_type_ = type; }
  void SetVerticesType(int type) { vertices_type_ = type; }
  void SetProjectionType(int type) { projection_type_ = type; }
  void SetVerticesSize(float size) { vertices_size_ = size; }
  void SetEdgesThickness(float size) { edges_thickness_ = size; }
  void TranslateFigureX(float translateX);
  void TranslateFigureY(float translateY);
  void TranslateFigureZ(float translateZ);
  void RotateFigureX(float rotateX);
  void RotateFigureY(float rotateY);
  void RotateFigureZ(float rotateZ);
  void ScaleFigure(float scale);
  bool isEmpty() { return figures_.empty(); }

 protected:
  void initializeGL() override;
  void initShaders();

 private:
  QOpenGLShaderProgram shaders_{};
  QMatrix4x4 projection_{};

  std::vector<std::unique_ptr<s21::Figure>> figures_;
  s21::ParserController parser_;

  QColor background_color_{};
  QColor edges_color_{};
  QColor vertices_color_{};
  int edges_type_ = 0;
  int vertices_type_ = 0;
  int projection_type_ = 0;
  float vertices_size_ = 1;
  float edges_thickness_ = 1;
};

#endif  // SRC_VIEWS_VIEWER_WIDGET_H_
