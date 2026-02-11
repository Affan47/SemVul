IndexOf(const SamReadGroup& readGroup) const {
    SamReadGroupConstIterator begin = ConstBegin();
    SamReadGroupConstIterator iter  = begin;
    SamReadGroupConstIterator end   = ConstEnd();
    for ( ; iter != end; ++iter ) {
        if ( *iter == readGroup )
            break;
    }
    return distance( begin, iter );
}
