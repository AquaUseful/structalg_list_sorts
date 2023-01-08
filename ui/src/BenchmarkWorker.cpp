#include "BenchmarkWorker.hpp"

#include <cmath>
#include <cstdint>
#include <qsplineseries.h>
#include <qobject.h>
#include <qobjectdefs.h>
#include <qpoint.h>
#include <iostream>

ui::BenchmarkWorker::BenchmarkWorker(QObject* parent) : QObject(parent) {
  qRegisterMetaType<measurement_t>("measurement_t");
}

void ui::BenchmarkWorker::startMeasurementsRandom(std::size_t size) {
  m_benchmark.resize(size);
  m_benchmark.fill_random();
  startMeasurements();
};
void ui::BenchmarkWorker::startMeasurementsSorted(std::size_t size) {
  m_benchmark.resize(size);
  m_benchmark.fill_sorted();
  startMeasurements();
};
void ui::BenchmarkWorker::startMeasurementsRevSorted(std::size_t size) {
  m_benchmark.resize(size);
  m_benchmark.fill_rev_sorted();
  startMeasurements();
};
void ui::BenchmarkWorker::startMeasurementsPartlySorted(std::size_t size, std::uint8_t percent) {
  m_benchmark.resize(size);
  m_benchmark.fill_partly_sorted(percent);
  startMeasurements();
};

void ui::BenchmarkWorker::startMeasurements() {

  std::cout << "test\n";

  auto linear_series = new QtCharts::QSplineSeries {};
  auto quick_series = new QtCharts::QSplineSeries {};
  auto shell_series = new QtCharts::QSplineSeries {};

  linear_series->setName("Линейная");
  quick_series->setName("Быстрая");
  shell_series->setName("Шелла (/1000)");

  constexpr std::uint8_t step_grow = 1;
  for (std::uint8_t p = 0; p <= 100; p += step_grow) {
    const measurement_t measurement = m_benchmark.measure(p);

    const auto linear_point = QPointF(p, measurement.linear_time.count());
    const auto quick_point = QPointF(p, measurement.quick_time.count());
    const auto shell_point = QPointF(p, measurement.shell_time.count() / 1000.0);

    linear_series->append(linear_point);
    quick_series->append(quick_point);
    shell_series->append(shell_point);

    emit measurementStepFinished(p, measurement);
  }

  emit measurementsFinished(linear_series, quick_series, shell_series);
}
