insert( double pos, const QColor &color )
{


    if ( pos < 0.0 || pos > 1.0 )
        return;

    int index;
    if ( _stops.size() == 0 )
    {
        index = 0;
        _stops.resize( 1 );
    }
    else
    {
        index = findUpper( pos );
        if ( index == _stops.size() ||
                qAbs( _stops[index].pos - pos ) >= 0.001 )
        {
            _stops.resize( _stops.size() + 1 );
            for ( int i = _stops.size() - 1; i > index; i-- )
                _stops[i] = _stops[i-1];
        }
    }

    _stops[index] = ColorStop( pos, color );
}
