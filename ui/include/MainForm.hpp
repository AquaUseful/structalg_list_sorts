#pragma once

#include "ui_MainForm.h"
#include <memory>
#include <qlayoutitem.h>
#include <qmainwindow.h>
#include <qobjectdefs.h>

namespace ui {
  class MainForm : public QMainWindow {

    Q_OBJECT

  public:
    explicit MainForm(QWidget* = nullptr);
    virtual ~MainForm() = default;

  private:
    std::unique_ptr<Ui::MainWindow> ui;
  };
} // namespace ui