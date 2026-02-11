bpm() const
{
    if( d->realTrack )
        return d->realTrack->bpm();
    else
        return d->cachedBpm;
}
