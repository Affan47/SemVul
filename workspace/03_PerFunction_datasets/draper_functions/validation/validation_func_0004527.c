operator[]( const char *key ) const
{
   JSON_ASSERT( type_ == nullValue  ||  type_ == objectValue );
   if ( type_ == nullValue )
      return null;
#ifndef JSON_VALUE_USE_INTERNAL_MAP
   CZString actualKey( key, CZString::noDuplication );
   ObjectValues::const_iterator it = value_.map_->find( actualKey );
   if ( it == value_.map_->end() )
      return null;
   return (*it).second;
#else
   const Value *value = value_.map_->find( key );
   return value ? *value : null;
#endif
}
