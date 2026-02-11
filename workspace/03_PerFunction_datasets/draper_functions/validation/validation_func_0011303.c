loadPlaylistFile( const KUrl &url, PlaylistFileProvider *provider )
{


    if( !url.isValid() )
    {
        error() << "url is not valid!";
        return PlaylistFilePtr();
    }

    if( url.isLocalFile() )
    {
        if( !QFileInfo( url.toLocalFile() ).exists() )
        {
            error() << QString("Could not load local playlist file %1!").arg( url.toLocalFile() );
            return PlaylistFilePtr();
        }
    }

    PlaylistFormat format = Playlists::getFormat( url );
    PlaylistFilePtr playlist;
    switch( format )
    {
        case ASX:
            playlist = new ASXPlaylist( url, provider );
            break;
        case PLS:
            playlist = new PLSPlaylist( url, provider );
            break;
        case M3U:
            playlist = new M3UPlaylist( url, provider );
            break;
        case XSPF:
            playlist = new XSPFPlaylist( url, provider );
            break;
        default:
            debug() << "Could not load playlist file " << url;
            break;
    }

    return playlist;
}
