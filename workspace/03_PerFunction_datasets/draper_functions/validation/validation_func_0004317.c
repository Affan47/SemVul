RemoveNameFilterMapping( const QRegExp& rx ) {
    for( NameFilterMap::iterator i = nameFilterMap_.begin();
         i != nameFilterMap_.end(); ++i ) {
        if( i->first == rx ) {
            nameFilterMap_.erase( i );
            break;
        }
    }
}
