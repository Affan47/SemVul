partialUpdate( const FractalData* data )
{
    const QList<QRect> validRegions = data->validRegions();

    if ( validRegions.count() > 0 && validRegions.first().top() == 0 && validRegions.first().bottom() > m_updatedRegion.bottom() ) {
        int top = qMax( m_updatedRegion.bottom() - 1, 0 );
        QRect region( 0, top, validRegions.first().width() - 2, validRegions.first().bottom() - top - 1 );
        drawImage( data, region );
        m_updatedRegion = validRegions.first();

        update( worldTransform().mapRect( region ).adjusted( -1, -1, 1, 1 ) );
    }
}
