operator=( const atomList_t &alist )
{
  clear();
  for( size_t i = 0; i < alist.size(); ++i )
    insert( alist.atom( i ) );
  return( *this );
}
