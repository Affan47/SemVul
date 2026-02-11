set_bookmark( const int number, const bool set )
{
    if( ! m_vec_bookmark.size() ) get_nodetree();
    if( number <= 0 || number > MAX_RESNUMBER ) return;

    if( ! m_vec_bookmark.size() ) m_vec_bookmark.resize( MAX_RESNUMBER );

    m_save_info = true;
    m_vec_bookmark[ number ] = set;
}
