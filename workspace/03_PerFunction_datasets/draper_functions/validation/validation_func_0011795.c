setComment( const char* name, const char* comment ) const
{
   herr_t ret_value = H5Oset_comment_by_name( getLocId(), name, comment, H5P_DEFAULT );
   if( ret_value < 0 )
      throwException("setComment", "H5Oset_comment_by_name failed");
}
