getBorderDistHint( const QFont &font,
                                      int &start, int &end ) const
{
    start = 0;
    end = 0;

    if ( !hasComponent( QwtAbstractScaleDraw::Labels ) )
        return;

    const QList<double> &ticks = scaleDiv().ticks( QwtScaleDiv::MajorTick );
    if ( ticks.count() == 0 )
        return;


    double minTick = ticks[0];
    double minPos = scaleMap().transform( minTick );
    double maxTick = minTick;
    double maxPos = minPos;

    for ( int i = 1; i < ticks.count(); i++ )
    {
        const double tickPos = scaleMap().transform( ticks[i] );
        if ( tickPos < minPos )
        {
            minTick = ticks[i];
            minPos = tickPos;
        }
        if ( tickPos > scaleMap().transform( maxTick ) )
        {
            maxTick = ticks[i];
            maxPos = tickPos;
        }
    }

    double e = 0.0;
    double s = 0.0;
    if ( orientation() == Qt::Vertical )
    {
        s = -labelRect( font, minTick ).top();
        s -= qAbs( minPos - qRound( scaleMap().p2() ) );

        e = labelRect( font, maxTick ).bottom();
        e -= qAbs( maxPos - scaleMap().p1() );
    }
    else
    {
        s = -labelRect( font, minTick ).left();
        s -= qAbs( minPos - scaleMap().p1() );

        e = labelRect( font, maxTick ).right();
        e -= qAbs( maxPos - scaleMap().p2() );
    }

    if ( s < 0.0 )
        s = 0.0;
    if ( e < 0.0 )
        e = 0.0;

    start = qCeil( s );
    end = qCeil( e );
}
