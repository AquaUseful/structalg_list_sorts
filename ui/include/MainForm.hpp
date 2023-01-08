#pragma once

#include "BenchmarkWorker.hpp"
#include "ui_MainForm.h"
#include <cstddef>
#include <cstdint>
#include <memory>
#include <qlayoutitem.h>
#include <qmainwindow.h>
#include <qobjectdefs.h>

using std::size_t;
using std::uint8_t;

namespace ui {
  class MainForm : public QMainWindow {

    Q_OBJECT

  public:
    using measurement_t = typename BenchmarkWorker::measurement_t;

  public:
    explicit MainForm(QWidget* = nullptr);
    virtual ~MainForm() = default;

  private slots:
    void bench();
    void measureProgress(uint8_t, measurement_t);
    void measureFinish(QtCharts::QSplineSeries*, QtCharts::QSplineSeries*, QtCharts::QSplineSeries*);

  signals:
    void benchRandom(size_t);
    void benchSorted(size_t);
    void benchRevSorted(size_t);
    void benchPartSorted(size_t, uint8_t);

  private:
    void configureSlots();

  private:
    std::unique_ptr<Ui::MainWindow> ui;

    QThread* m_bench_thread;
    BenchmarkWorker* m_bench_worker;
  };
} // namespace ui