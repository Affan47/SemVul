slotCopyTracks()
{
    if( !sender() )
        return;
    if( QAction *action = dynamic_cast<QAction *>( sender() ) )
        copyTracks( m_currentItems, m_currentCopyDestination[ action ], false );
}
