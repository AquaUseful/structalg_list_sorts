#pragma once

#include <cstddef>
#include <cstdint>
#include <forward_list>
#include <qsplineseries.h>
#include <qobject.h>
#include <qobjectdefs.h>
#include <qpoint.h>
#include <qlineseries.h>
#include <qchart.h>

#include "Benchmark.hpp"

namespace ui {
  class BenchmarkWorker : public QObject {

    Q_OBJECT

  public:
    using value_t = std::int32_t;

    using benchmark_t = benchmark::Benchmark<std::forward_list<value_t>>;
    using measurement_t = typename benchmark_t::measurement_t;

    

  public:
    BenchmarkWorker(QObject* = nullptr);
    virtual ~BenchmarkWorker() = default;

  signals:
    void measurementsFinished(QtCharts::QSplineSeries*, QtCharts::QSplineSeries*, QtCharts::QSplineSeries*);
    void measurementStepFinished(uint8_t, measurement_t);

  public slots:
    void startMeasurementsRandom(size_t);
    void startMeasurementsSorted(size_t);
    void startMeasurementsRevSorted(size_t);
    void startMeasurementsPartlySorted(size_t, uint8_t);

  private:
    void startMeasurements();

  private:
    benchmark_t m_benchmark {100};
  };
}