setPlaying( bool playing )
{
    if ( m_isPlaying == playing )
        return;

    setToolTip( playing ? i18n( "Pause" ) : i18n( "Play" ) );

    m_isPlaying = playing;
    setIcon( m_isPlaying ? m_icon.pause[underMouse()] : m_icon.play[underMouse()], 4 );
}
