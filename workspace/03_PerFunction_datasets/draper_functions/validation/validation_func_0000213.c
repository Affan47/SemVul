divideScale( double x1, double x2,
    int maxMajSteps, int maxMinSteps, double stepSize ) const
{
    QwtInterval interval = QwtInterval( x1, x2 ).normalized();
    interval = interval.limited( LOG_MIN, LOG_MAX );

    if ( interval.width() <= 0 )
        return QwtScaleDiv();

    if ( interval.maxValue() / interval.minValue() < 10.0 )
    {


        QwtLinearScaleEngine linearScaler;
        linearScaler.setAttributes( attributes() );
        linearScaler.setReference( reference() );
        linearScaler.setMargins( lowerMargin(), upperMargin() );

        if ( stepSize != 0.0 )
            stepSize = qPow( 10.0, stepSize );

        return linearScaler.divideScale( x1, x2,
            maxMajSteps, maxMinSteps, stepSize );
    }

    stepSize = qAbs( stepSize );
    if ( stepSize == 0.0 )
    {
        if ( maxMajSteps < 1 )
            maxMajSteps = 1;

        stepSize = divideInterval( log10( interval ).width(), maxMajSteps );
        if ( stepSize < 1.0 )
            stepSize = 1.0;
    }

    QwtScaleDiv scaleDiv;
    if ( stepSize != 0.0 )
    {
        QList<double> ticks[QwtScaleDiv::NTickTypes];
        buildTicks( interval, stepSize, maxMinSteps, ticks );

        scaleDiv = QwtScaleDiv( interval, ticks );
    }

    if ( x1 > x2 )
        scaleDiv.invert();

    return scaleDiv;
}
