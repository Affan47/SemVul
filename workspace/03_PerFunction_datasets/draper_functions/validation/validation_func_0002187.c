metricForSymbol(QString symbol)
{
    const RideMetricFactory &factory = RideMetricFactory::instance();
    return factory.rideMetric(symbol);
}
