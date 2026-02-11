loadCover()
{
    const bool isSuppressing = m_albumPtr->suppressImageAutoFetch();
    m_albumPtr->setSuppressImageAutoFetch( true );
    setIcon( QPixmap::fromImage( m_albumPtr->image( 100 ) ) );
    m_albumPtr->setSuppressImageAutoFetch( isSuppressing );
}
