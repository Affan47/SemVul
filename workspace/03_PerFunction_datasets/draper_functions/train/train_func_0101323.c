filterMatches( Meta::TrackPtr track ) const
{
    return !m_filter->filterMatches( track );
}
