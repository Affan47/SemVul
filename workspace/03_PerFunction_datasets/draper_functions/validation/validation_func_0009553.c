notPlayableReason() const
{
    if( !m_playableUrl.isEmpty() && playableUrl().isLocalFile() )
        return localFileNotPlayableReason( m_playableUrl );

    if( !m_downloadableUrl.isEmpty() )
        return networkNotPlayableReason();

    return i18n( "Neither playable nor downloadable url specified." );
}
