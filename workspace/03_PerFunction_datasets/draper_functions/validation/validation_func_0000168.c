setFontSize( int size )
{
    QFontMetricsF metrics( fontMetrics() );
    QRectF rect;

    d->fontsize = size;

    d->m_maxCell.setWidth( 0 );
    d->m_maxCell.setHeight( 0 );
    for( int weekday = 1; weekday <= d->m_date.daysInWeek(); ++weekday ) {
        rect = metrics.boundingRect( calendar()->weekDayName( weekday, KCalendarSystem::ShortDayName ) );
        d->m_maxCell.setWidth( qMax( d->m_maxCell.width(), rect.width() ) );
        d->m_maxCell.setHeight( qMax( d->m_maxCell.height(), rect.height() ) );
    }

    rect = metrics.boundingRect( QLatin1String( "88" ) );
    d->m_maxCell.setWidth( qMax( d->m_maxCell.width() + 2, rect.width() ) );
    d->m_maxCell.setHeight( qMax( d->m_maxCell.height() + 4, rect.height() ) );
}
