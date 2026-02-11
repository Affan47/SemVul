findRangeAction( const DateRange& range )
{

    for ( QHash<QAction*, DateRange>::const_iterator it = m_rangeActionMap.constBegin();
          it != m_rangeActionMap.constEnd(); ++it ) {
        if ( it.value() == range )
            return it.key();
    }
    return 0;
}
