entitiesDiffer( const Meta::Album *first, const Meta::Album *second )
{
    if( !first && !second )
        return false;
    if( !first || !second )
        return true;

    if( first->name() != second->name() )
        return true;
    if( first->isCompilation() != second->isCompilation() )
        return true;
    if( first->hasImage() != second->hasImage() )
        return true;
    if( entitiesDiffer( first->albumArtist().data(), second->albumArtist().data() ) )
        return true;


    if( first->image().width() != second->image().width() )
        return true;
    if( first->image().height() != second->image().height() )
        return true;

    return false;
}
