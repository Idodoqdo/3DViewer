// Copyright 2022 <lwolmer, jgerrick, lshiela>
#include "viewer_widget.h"

#include <QMouseEvent>
#include <cmath>

#include "figure.h"

ViewerWidget::~ViewerWidget() { figures_.clear(); }

ViewerWidget::ViewerWidget(QWidget *parent, Qt::WindowFlags f)
    : QOpenGLWidget(parent, f) {
  // Generate 2 VBOs
}

void ViewerWidget::initializeGL() {
  initializeOpenGLFunctions();
  glClearColor(0.0, 0.0, 1.0, 0.0);
  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  initShaders();
}

int ViewerWidget::GetFigureEdgesCount(size_t index) const {
  return figures_.at(index).get()->GetEdgesCount();
}
int ViewerWidget::GetFigureVerticesCount(size_t index) const {
  return figures_.at(index).get()->GetVerticesCount();
}

void ViewerWidget::TranslateFigureX(float translateX) {
  figures_.at(0)->TranslateX(translateX);
}

void ViewerWidget::TranslateFigureY(float translateY) {
  figures_.at(0)->TranslateY(translateY);
}

void ViewerWidget::TranslateFigureZ(float translateZ) {
  figures_.at(0)->TranslateZ(translateZ);
}

void ViewerWidget::RotateFigureX(float rotateX) {
  figures_.at(0)->RotateX(qDegreesToRadians(rotateX));
}

void ViewerWidget::RotateFigureY(float rotateY) {
  figures_.at(0)->RotateY(qDegreesToRadians(rotateY));
}

void ViewerWidget::RotateFigureZ(float rotateZ) {
  figures_.at(0)->RotateZ(qDegreesToRadians(rotateZ));
}

void ViewerWidget::ScaleFigure(float scale) { figures_.at(0)->Scale(scale); }

void ViewerWidget::initShaders() {
  // Compile vertex shader
  if (!shaders_.addShaderFromSourceFile(QOpenGLShader::Vertex,
                                        ":vertex_shader"))
    qFatal("No vertex shader");

  // Compile fragment shader
  if (!shaders_.addShaderFromSourceFile(QOpenGLShader::Fragment,
                                        ":fragment_shader"))
    qFatal("No fragment shader");

  // Link shader pipeline
  if (!shaders_.link()) close();

  // Bind shader pipeline for use
  if (!shaders_.bind()) close();
}

void ViewerWidget::resizeGL(int w, int h) {
  // Calculate aspect ratio
  qreal aspect = qreal(w) / qreal(h ? h : 1);

  // Set near plane to 3.0, far plane to 7.0, field of view 45 degrees
  const qreal zNear = 0.1, zFar = 10000.0, fov = 70.0;
  // Reset projection
  projection_.setToIdentity();

  // Set perspective projection
  if (projection_type_ == 0) {
    projection_.perspective(fov, static_cast<float>(aspect),
                            static_cast<float>(zNear), zFar);
  } else {
    projection_.ortho(static_cast<float>(-aspect), static_cast<float>(aspect),
                      -1.0, 1.0, static_cast<float>(zNear), zFar);
  }
}

void ViewerWidget::paintGL() {
  glClearColor(background_color_.redF(), background_color_.greenF(),
               background_color_.blueF(), background_color_.alphaF());
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // Draw lines
  if (edges_type_ == 0) {
    glDisable(GL_LINE_STIPPLE);
    glEnable(GL_LINES);
  } else if (edges_type_ == 1) {
    glLineStipple(5, 0x00FF);
    glEnable(GL_LINE_STIPPLE);
  }

  // Draw dots
  if (vertices_type_ == 0) {
    glDisable(GL_POINT_SMOOTH);
  } else {
    if (vertices_type_ == 1) {
      glEnable(GL_POINT_SMOOTH);
    } else if (vertices_type_ == 2) {
      glDisable(GL_POINT_SMOOTH);
    }
    glPointSize(vertices_size_);
    glUniform4f(LINES_BIND_LOC, vertices_color_.redF(),
                vertices_color_.greenF(), vertices_color_.blueF(),
                vertices_color_.alphaF());
  }

  glLineWidth(edges_thickness_);
  glUniform4f(LINES_BIND_LOC, edges_color_.redF(), edges_color_.greenF(),
              edges_color_.blueF(), edges_color_.alphaF());

  for (auto &figure : figures_) {
    figure.get()->BindData();
    figure.get()->Draw();
  }
}

void ViewerWidget::LoadModel(QString path) {
  if (path.length()) {
    figures_.clear();
    figures_.shrink_to_fit();
    figures_.push_back(
        std::make_unique<s21::Figure>(path.toStdString(), parser_, *this));
  }
}
