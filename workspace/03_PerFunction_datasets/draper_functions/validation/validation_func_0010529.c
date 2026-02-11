builtin_check_if_file( FRAME * frame, int flags )
{
    LIST * name = lol_get( frame->args, 0 );
    return file_is_file( list_front( name ) ) == 1
        ? list_new( object_copy( constant_true ) )
        : L0 ;
}
