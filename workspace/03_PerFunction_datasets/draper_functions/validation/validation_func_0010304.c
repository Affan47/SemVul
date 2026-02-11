updateMenu()
{
    foreach( QAction* action, m_extraActions )
    {
        contextMenu()->removeAction( action );

        if( action && !action->parent() )
        {
            delete action;
        }
    }
    m_extraActions.clear();

    contextMenu()->removeAction( m_separator.data() );

    delete m_separator.data();

    if( m_track )
    {
        foreach( QAction *action, The::globalCurrentTrackActions()->actions() )
            m_extraActions.append( action );

        QScopedPointer<Capabilities::ActionsCapability> ac( m_track->create<Capabilities::ActionsCapability>() );
        if( ac )
        {
            QList<QAction*> actions = ac->actions();
            foreach( QAction *action, actions )
                m_extraActions.append( action );
        }

        QScopedPointer<Capabilities::BookmarkThisCapability> btc( m_track->create<Capabilities::BookmarkThisCapability>() );
        if( btc )
        {
            m_extraActions.append( btc->bookmarkAction() );
        }
    }


    if( m_extraActions.count() > 0 ||
        contextMenu()->actions().last() != actionCollection()->action( "file_quit" ) )
    {

        contextMenu()->removeAction( actionCollection()->action( "file_quit" ) );
        contextMenu()->removeAction( actionCollection()->action( "minimizeRestore" ) );

        foreach( QAction* action, m_extraActions )
            contextMenu()->addAction( action );

        m_separator = contextMenu()->addSeparator();

        contextMenu()->addAction( actionCollection()->action( "minimizeRestore" ) );
        contextMenu()->addAction( actionCollection()->action( "file_quit" ) );
    }
}
