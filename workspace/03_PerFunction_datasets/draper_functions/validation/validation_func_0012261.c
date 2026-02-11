addBordersToPixmap( const QPixmap &orgPixmap, int borderWidth, const QString &name, bool skipCache )
{
    int newWidth = orgPixmap.width() + borderWidth * 2;
    int newHeight = orgPixmap.height() + borderWidth *2;

    QString key;
    if( !skipCache )
    {
        key = QString("%1:%2x%3b%4")
            .arg( name )
            .arg( newWidth )
            .arg( newHeight )
            .arg( borderWidth );
    }

    QPixmap pixmap;
    if( skipCache || !m_cache->findPixmap( key, &pixmap ) )
    {


        pixmap = QPixmap( newWidth, newHeight );
        pixmap.fill( Qt::transparent );

        QReadLocker readLocker( &m_lock );
        if( !m_renderers[m_themeFile] )
        {
            readLocker.unlock();
            if( !loadSvg( m_themeFile ) )
            {
                return pixmap;
            }
            readLocker.relock();
        }

        QPainter pt( &pixmap );

        pt.drawPixmap( borderWidth, borderWidth, orgPixmap.width(), orgPixmap.height(), orgPixmap );

        m_renderers[m_themeFile]->render( &pt, "cover_border_topleft", QRectF( 0, 0, borderWidth, borderWidth ) );
        m_renderers[m_themeFile]->render( &pt, "cover_border_top", QRectF( borderWidth, 0, orgPixmap.width(), borderWidth ) );
        m_renderers[m_themeFile]->render( &pt, "cover_border_topright", QRectF( newWidth - borderWidth , 0, borderWidth, borderWidth ) );
        m_renderers[m_themeFile]->render( &pt, "cover_border_right", QRectF( newWidth - borderWidth, borderWidth, borderWidth, orgPixmap.height() ) );
        m_renderers[m_themeFile]->render( &pt, "cover_border_bottomright", QRectF( newWidth - borderWidth, newHeight - borderWidth, borderWidth, borderWidth ) );
        m_renderers[m_themeFile]->render( &pt, "cover_border_bottom", QRectF( borderWidth, newHeight - borderWidth, orgPixmap.width(), borderWidth ) );
        m_renderers[m_themeFile]->render( &pt, "cover_border_bottomleft", QRectF( 0, newHeight - borderWidth, borderWidth, borderWidth ) );
        m_renderers[m_themeFile]->render( &pt, "cover_border_left", QRectF( 0, borderWidth, borderWidth, orgPixmap.height() ) );

        if( !skipCache )
            m_cache->insertPixmap( key, pixmap );
    }

    return pixmap;
}
