withoutDuplicate( int position, const Meta::TrackList& playlist,
                              const Dynamic::TrackSet& oldSet )
{
    Dynamic::TrackSet result = Dynamic::TrackSet( oldSet );
    for( int i = 0; i < playlist.count(); i++ )
        if( i != position && playlist[i] )
            result.subtract( playlist[i] );

    return result;
}
