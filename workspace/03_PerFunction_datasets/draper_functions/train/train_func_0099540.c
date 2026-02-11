allChildPlaylists() const
{
    SqlPlaylistList playlists;
    playlists << childSqlPlaylists();
    foreach( SqlPlaylistGroupPtr childGroup, childSqlGroups() )
    {
        playlists << childGroup->allChildPlaylists();
    }
    return playlists;
}
