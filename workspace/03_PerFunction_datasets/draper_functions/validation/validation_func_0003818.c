queryDone()
{
    delete m_queryMaker;
    if( !m_tracks.isEmpty() )
    {
        initUi();
        setCurrentTrack( 0 );

        QTimer::singleShot( 0, this, SLOT(show()) );
    }
    else
    {
        deleteLater();
    }
}
