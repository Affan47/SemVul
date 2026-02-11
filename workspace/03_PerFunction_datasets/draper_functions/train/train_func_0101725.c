setYear( int newYear )
{
    if( !m_collection )
        return;

    MediaDeviceYearPtr yearPtr;
    MediaDeviceTrackPtr track( this );
    YearMap yearMap = m_collection.data()->memoryCollection()->yearMap();


    yearPtr = m_year;
    if ( !yearPtr.isNull() )
    {

        yearPtr->remTrack( track );

        if( yearPtr->tracks().isEmpty() )
            yearMap.remove( yearPtr->year() );
    }


    if ( yearMap.contains( newYear ) )
    {
        yearPtr = MediaDeviceYearPtr::staticCast( yearMap.value( newYear ) );
    }
    else
    {
        yearPtr = MediaDeviceYearPtr( new MediaDeviceYear( QString::number(newYear) ) );
        yearMap.insert( newYear, YearPtr::staticCast( yearPtr ) );
    }


    yearPtr->addTrack( track );

    setYear( yearPtr );

    m_collection.data()->memoryCollection()->acquireWriteLock();
    m_collection.data()->memoryCollection()->setYearMap( yearMap );
    m_collection.data()->memoryCollection()->releaseLock();
}
