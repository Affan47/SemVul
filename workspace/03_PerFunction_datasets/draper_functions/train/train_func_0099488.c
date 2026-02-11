mimeData( const QModelIndexList &indices ) const
{
    AmarokMimeData* mime = new AmarokMimeData();

    Playlists::PlaylistList playlists;
    Meta::TrackList tracks;

    foreach( const QModelIndex &index, indices )
    {
        if( IS_TRACK(index) )
            tracks << trackFromIndex( index );
        else
            playlists << m_playlists.value( index.internalId() );
    }

    mime->setPlaylists( playlists );
    mime->setTracks( tracks );

    return mime;
}
