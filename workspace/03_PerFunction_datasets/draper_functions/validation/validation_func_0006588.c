editor()
{
    if( m_tracks.count() == 1 )
        return m_tracks.first()->editor();

    QList<Meta::TrackEditorPtr> editors;
    foreach( Meta::TrackPtr track, m_tracks )
    {
        Meta::TrackEditorPtr ec = track->editor();
        if( ec )
            editors << ec;
        else
            return TrackEditorPtr();
    }
    return TrackEditorPtr( new AggregateTrackEditor( m_collection, editors ) );
}
