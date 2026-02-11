GetPageState( int page ) const
{


    if ( page >= (int)GetPageCount() )
        return NULL;

    if ( page == -1 )
        return m_pState;
    return GETPAGESTATE(page);
}
