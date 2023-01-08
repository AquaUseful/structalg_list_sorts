#include "MainForm.hpp"
#include "BenchmarkWorker.hpp"
#include "ui_MainForm.h"
#include <cstddef>
#include <cstdint>
#include <memory>
#include <qmainwindow.h>
#include <qobjectdefs.h>
#include <qwidget.h>

ui::MainForm::MainForm(QWidget* parent)
  : QMainWindow(parent),
    ui {std::make_unique<Ui::MainWindow>()},
    m_bench_thread {new QThread(this)},
    m_bench_worker {new BenchmarkWorker()} {
  ui->setupUi(this);
  ui->retranslateUi(this);
  configureSlots();
  m_bench_worker->moveToThread(m_bench_thread);
  m_bench_thread->start();
  ui->chart->setRenderHint(QPainter::Antialiasing);
}

void ui::MainForm::configureSlots() {
  qRegisterMetaType<size_t>("size_t");
  qRegisterMetaType<uint8_t>("uint8_t");

  connect(this, SIGNAL(benchRandom(size_t)), m_bench_worker, SLOT(startMeasurementsRandom(size_t)));
  connect(this, SIGNAL(benchSorted(size_t)), m_bench_worker, SLOT(startMeasurementsSorted(size_t)));
  connect(this, SIGNAL(benchRevSorted(size_t)), m_bench_worker, SLOT(startMeasurementsRevSorted(size_t)));
  connect(this, SIGNAL(benchPartSorted(size_t, uint8_t)), m_bench_worker, SLOT(startMeasurementsPartlySorted(size_t, uint8_t)));

  connect(m_bench_worker, SIGNAL(measurementStepFinished(uint8_t, measurement_t)), this, SLOT(measureProgress(uint8_t, measurement_t)));
  connect(m_bench_worker,
          SIGNAL(measurementsFinished(QtCharts::QSplineSeries*, QtCharts::QSplineSeries*, QtCharts::QSplineSeries*)),
          this,
          SLOT(measureFinish(QtCharts::QSplineSeries*, QtCharts::QSplineSeries*, QtCharts::QSplineSeries*)));

  connect(ui->updateChart, SIGNAL(clicked()), this, SLOT(bench()));
}

void ui::MainForm::bench() {
  ui->table->setRowCount(0);
  if (ui->radioUnsorted->isChecked()) {
    emit benchRandom(ui->maxElements->value());
  } else if (ui->radioSorted->isChecked()) {
    emit benchSorted(ui->maxElements->value());
  } else if (ui->radioReverse->isChecked()) {
    emit benchRevSorted(ui->maxElements->value());
  } else if (ui->radioPartly->isChecked()) {
    emit benchPartSorted(ui->maxElements->value(), ui->sortedPercent->value());
  }
}

void ui::MainForm::measureProgress(uint8_t percent, measurement_t measurement) {
  ui->chartProgress->setValue(percent);

  const auto percent_item = new QTableWidgetItem(QString::number(percent));
  const auto shell_item = new QTableWidgetItem(QString::number(measurement.shell_time.count()));
  const auto quick_item = new QTableWidgetItem(QString::number(measurement.quick_time.count()));
  const auto linear_item = new QTableWidgetItem(QString::number(measurement.linear_time.count()));

  const auto free_row = ui->table->rowCount();
  ui->table->setRowCount(free_row + 1);

  ui->table->setItem(free_row, 0, percent_item);
  ui->table->setItem(free_row, 1, shell_item);
  ui->table->setItem(free_row, 2, quick_item);
  ui->table->setItem(free_row, 3, linear_item);
}

void ui::MainForm::measureFinish(QtCharts::QSplineSeries* s1, QtCharts::QSplineSeries* s2, QtCharts::QSplineSeries* s3) {
  auto chart = new QtCharts::QChart();
  chart->addSeries(s1);
  chart->addSeries(s2);
  chart->addSeries(s3);
  chart->createDefaultAxes();

  ui->chart->setChart(chart);
}
