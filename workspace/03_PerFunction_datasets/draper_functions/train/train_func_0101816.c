apply_modifiers_non_empty( LIST * result, string * buf, VAR_EDITS * edits, int n, LISTITER begin, LISTITER end )
{
    int i;
    LISTITER iter;
    for ( i = 0; i < n; ++i )
    {
        if ( edits[i].join.ptr )
        {
            var_edit_file( object_str( list_item( begin ) ), buf, edits + i );
            var_edit_shift( buf, 0, edits + i );
            for ( iter = list_next( begin ); iter != end; iter = list_next( iter ) )
            {
                size_t size;
                string_append( buf, edits[i].join.ptr );
                size = buf->size;
                var_edit_file( object_str( list_item( iter ) ), buf, edits + i );
                var_edit_shift( buf, size, edits + i );
            }
            result = list_push_back( result, object_new( buf->value ) );
            string_truncate( buf, 0 );
        }
        else
        {
            for ( iter = begin; iter != end; iter = list_next( iter ) )
            {
                var_edit_file( object_str( list_item( iter ) ), buf, edits + i );
                var_edit_shift( buf, 0, edits + i );
                result = list_push_back( result, object_new( buf->value ) );
                string_truncate( buf, 0 );
            }
        }
    }
    return result;
}
