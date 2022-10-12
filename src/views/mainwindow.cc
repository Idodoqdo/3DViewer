// Copyright 2022 <lwolmer, jgerrick, lshiela>
#include "mainwindow.h"

#include <QMessageBox>
#include <limits>

#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  QTimer::singleShot(0, this, SLOT(OnWidgetLoad()));
}

void MainWindow::SaveSettings() {
  settings_->SaveElement(*ui->edges_thickness_slider);
  settings_->SaveElement(*ui->edges_type_combobox);
  settings_->SaveElement(*ui->vertices_size_slider);
  settings_->SaveElement(*ui->vertices_type_combobox);
  settings_->SaveVariable("background_color", bg_color_);
  settings_->SaveVariable("edges_color", edges_color_);
  settings_->SaveVariable("vertices_color", vertices_color_);
}

void MainWindow::LoadSettings() {
  gl_widget_ = ui->gl_widget;
  bg_color_ = QColor(QColorConstants::Black);
  edges_color_ = QColor(QColorConstants::Green);
  vertices_color_ = QColor(QColorConstants::DarkGreen);
  settings_->LoadElement(ui->edges_thickness_slider);
  settings_->LoadElement(ui->edges_type_combobox);
  settings_->LoadElement(ui->vertices_size_slider);
  settings_->LoadElement(ui->vertices_type_combobox);
  settings_->LoadVariable("background_color", &bg_color_);
  settings_->LoadVariable("edges_color", &edges_color_);
  settings_->LoadVariable("vertices_color", &vertices_color_);
}

void MainWindow::ApplySettings() {
  OnProjectionTypeChange();
  OnEdgeThicknessChange();
  OnEdgeTypeChange();
  OnVertexSizeChange();
  OnVertexTypeChange();
  OnBGColorChange();
  OnEdgeColorChange();
  OnVertexColorChange();
}

void MainWindow::OnWidgetLoad() {
  InitValidators();
  ConnectToSignals();
  settings_ = new ViewerSettings(QCoreApplication::applicationDirPath() + "/settings.ini", QSettings::IniFormat, this);
  LoadSettings();
  ApplySettings();
}

void MainWindow::InitValidators() {
  QIntValidator *angle_validator = new QIntValidator(-999, 999, this);
  QDoubleValidator *positive_validator =
      new QDoubleValidator(0, std::numeric_limits<double>::max(), 2, this);
  QValidator *validator =
      new QDoubleValidator(-std::numeric_limits<double>::max(),
                           std::numeric_limits<double>::max(), 2, this);
  ui->scale_lineedit->setValidator(positive_validator);
  ui->rotate_x_lineedit->setValidator(angle_validator);
  ui->rotate_y_lineedit->setValidator(angle_validator);
  ui->rotate_z_lineedit->setValidator(angle_validator);
  ui->translate_x_lineedit->setValidator(validator);
  ui->translate_y_lineedit->setValidator(validator);
  ui->translate_z_lineedit->setValidator(validator);
};

void MainWindow::ConnectToSignals() {
  connect(ui->file_open_pushbutton, &QPushButton::clicked, this,
          &MainWindow::OnOpenFilePressed);
  connect(ui->translate_x_slider, &QSlider::sliderMoved, this, [=]() {
    this->OnChange(ui->translate_x_lineedit, ui->translate_x_slider,
                   &ViewerWidget::TranslateFigureX);
  });
  connect(ui->translate_x_lineedit, &QLineEdit::textEdited, this, [=]() {
    this->OnChange(ui->translate_x_lineedit, ui->translate_x_slider,
                   &ViewerWidget::TranslateFigureX);
  });
  connect(ui->translate_y_slider, &QSlider::sliderMoved, this, [=]() {
    this->OnChange(ui->translate_y_lineedit, ui->translate_y_slider,
                   &ViewerWidget::TranslateFigureY);
  });
  connect(ui->translate_y_lineedit, &QLineEdit::textEdited, this, [=]() {
    this->OnChange(ui->translate_y_lineedit, ui->translate_y_slider,
                   &ViewerWidget::TranslateFigureY);
  });
  connect(ui->translate_z_slider, &QSlider::sliderMoved, this, [=]() {
    this->OnChange(ui->translate_z_lineedit, ui->translate_z_slider,
                   &ViewerWidget::TranslateFigureZ);
  });
  connect(ui->translate_z_lineedit, &QLineEdit::textEdited, this, [=]() {
    this->OnChange(ui->translate_z_lineedit, ui->translate_z_slider,
                   &ViewerWidget::TranslateFigureZ);
  });
  connect(ui->rotate_x_slider, &QSlider::sliderMoved, this, [=]() {
    this->OnChange(ui->rotate_x_lineedit, ui->rotate_x_slider,
                   &ViewerWidget::RotateFigureX);
  });
  connect(ui->rotate_x_lineedit, &QLineEdit::textEdited, this, [=]() {
    this->OnChange(ui->rotate_x_lineedit, ui->rotate_x_slider,
                   &ViewerWidget::RotateFigureX);
  });
  connect(ui->rotate_y_slider, &QSlider::sliderMoved, this, [=]() {
    this->OnChange(ui->rotate_y_lineedit, ui->rotate_y_slider,
                   &ViewerWidget::RotateFigureY);
  });
  connect(ui->rotate_y_lineedit, &QLineEdit::textEdited, this, [=]() {
    this->OnChange(ui->rotate_y_lineedit, ui->rotate_y_slider,
                   &ViewerWidget::RotateFigureY);
  });
  connect(ui->rotate_z_slider, &QSlider::sliderMoved, this, [=]() {
    this->OnChange(ui->rotate_z_lineedit, ui->rotate_z_slider,
                   &ViewerWidget::RotateFigureZ);
  });
  connect(ui->rotate_z_lineedit, &QLineEdit::textEdited, this, [=]() {
    this->OnChange(ui->rotate_z_lineedit, ui->rotate_z_slider,
                   &ViewerWidget::RotateFigureZ);
  });
  connect(ui->scale_slider, &QSlider::sliderMoved, this, [=]() {
    this->OnChange(ui->scale_lineedit, ui->scale_slider,
                   &ViewerWidget::ScaleFigure);
  });
  connect(ui->scale_lineedit, &QLineEdit::textEdited, this, [=]() {
    this->OnChange(ui->scale_lineedit, ui->scale_slider,
                   &ViewerWidget::ScaleFigure);
  });
  connect(ui->projection_combobox, &QComboBox::currentIndexChanged, this,
          &MainWindow::OnProjectionTypeChange);
  connect(ui->background_color_pushbutton, &QPushButton::clicked, this,
          &MainWindow::OnBGColorPressed);
  connect(ui->edges_type_combobox, &QComboBox::currentIndexChanged, this,
          &MainWindow::OnEdgeTypeChange);
  connect(ui->edges_color_pushbutton, &QPushButton::clicked, this,
          &MainWindow::OnEdgeColorPressed);
  connect(ui->edges_thickness_slider, &QSlider::sliderMoved, this,
          &MainWindow::OnEdgeThicknessChange);
  connect(ui->vertices_type_combobox, &QComboBox::currentIndexChanged, this,
          &MainWindow::OnVertexTypeChange);
  connect(ui->vertices_color_pushbutton, &QPushButton::clicked, this,
          &MainWindow::OnVertexColorPressed);
  connect(ui->vertices_size_slider, &QSlider::sliderMoved, this,
          &MainWindow::OnVertexSizeChange);
  connect(ui->printscreen_pushbutton, &QPushButton::clicked, this,
          &MainWindow::OnMakeScreenshootPressed);
  connect(ui->gif_pushbutton, &QPushButton::clicked, this,
          &MainWindow::OnMakeGifPressed);
  // TODO(lwolmer): Change icon back
  // connect(opengl_window_, &OpenGLWindow::GifRecorded, this, [this]()
  // {ui->gif_pushbutton->setText("Capture gif animation");});
}

void MainWindow::SetLabelPixmap(QLabel *label, QColor color) {
  QPixmap pixmap(16, 16);
  pixmap.fill(color);
  label->setPixmap(pixmap);
}

void MainWindow::OpenFile(QString path) {
  try {
    gl_widget_->LoadModel(path);
    void LoadModel(QString path);
    QFileInfo fullName(path);
    ui->file_name_output_label->setText(fullName.fileName());
    ui->num_of_vert_output_label->setText(
        QString::number(gl_widget_->GetFigureVerticesCount(0)));
    ui->num_of_edges_output_label->setText(
        QString::number(gl_widget_->GetFigureEdgesCount(0)));
    ApplySettings();
  } catch (const std::exception &e) {
    QMessageBox::critical(this, "Error", e.what(), QMessageBox::Ok);
  }
}

void MainWindow::OnOpenFilePressed() {
  QString fileName = QFileDialog::getOpenFileName(this, tr("Open Object file"),
                                                  QDir::homePath(),
                                                  tr("Object Files (*.obj)"));
  OpenFile(fileName);
}

void MainWindow::OnChange(QLineEdit *line, QSlider *slider,
                          void (ViewerWidget::*ptrFunc)(float)) {
  if (!gl_widget_->isEmpty()) {
    if (line->isModified()) {
      slider->setValue(line->text().toInt());
      line->setModified(false);
    } else {
      line->setText(QString::number(slider->value()));
    }
    (gl_widget_->*ptrFunc)(line->text().toFloat());
    gl_widget_->update();
  } else {
    QMessageBox::critical(this, "Error", "No model loaded", QMessageBox::Ok);
  }
}

void MainWindow::OnProjectionTypeChange() {
  int type = ui->projection_combobox->currentIndex();
  gl_widget_->SetProjectionType(type);
}

void MainWindow::OnBGColorPressed() {
  QColor color = QColorDialog::getColor(bg_color_, this, "Choose color");
  if (!color.isValid()) return;
  bg_color_ = color;
  OnBGColorChange();
}

void MainWindow::OnEdgeTypeChange() {
  int type = ui->edges_type_combobox->currentIndex();
  gl_widget_->SetEdgesType(type);
  gl_widget_->update();
}

void MainWindow::OnEdgeThicknessChange() {
  int size = ui->edges_thickness_slider->value();
  gl_widget_->SetEdgesThickness(size);
  gl_widget_->update();
}

void MainWindow::OnEdgeColorPressed() {
  QColor color = QColorDialog::getColor(edges_color_, this, "Choose color");
  if (!color.isValid()) return;
  edges_color_ = color;
  OnEdgeColorChange();
}

void MainWindow::OnVertexTypeChange() {
  int type = ui->vertices_type_combobox->currentIndex();
  gl_widget_->SetVerticesType(type);
  gl_widget_->update();
}

void MainWindow::OnVertexColorPressed() {
  QColor color = QColorDialog::getColor(vertices_color_, this, "Choose color");
  if (!color.isValid()) return;
  vertices_color_ = color;
  OnVertexColorChange();
}

void MainWindow::OnVertexSizeChange() {
  int size = ui->vertices_size_slider->value();
  gl_widget_->SetVerticesSize(size);
  gl_widget_->update();
}

void MainWindow::OnBGColorChange() {
  SetLabelPixmap(ui->background_color_label, bg_color_);
  gl_widget_->SetBackgroundColor(bg_color_);
}

void MainWindow::OnEdgeColorChange() {
  SetLabelPixmap(ui->edges_color_label, edges_color_);
  gl_widget_->SetEdgesColor(edges_color_);
}

void MainWindow::OnVertexColorChange() {
  SetLabelPixmap(ui->vertices_color_label, vertices_color_);
  gl_widget_->SetVerticesColor(vertices_color_);
}

void MainWindow::OnMakeScreenshootPressed() {
  QMessageBox::critical(this, "Error", "НЕТУ РЕАЛИЗАЦИИ, пока что...",
                        QMessageBox::Ok);
}

void MainWindow::OnMakeGifPressed() {
  QMessageBox::critical(this, "Error", "НЕТУ РЕАЛИЗАЦИИ, пока что...",
                        QMessageBox::Ok);
}

MainWindow::~MainWindow() {
  SaveSettings();
  delete ui;
}
