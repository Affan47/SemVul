fl_create_animated_cursor( int * cur_names,
                           int   timeout )
{
    int *n = cur_names,
        k = MAX_SEQ;
    CurStruct *c = 0;

    for ( ; *n >= 0 && --k >= 0; n++ )
        c = add_cursor( user_cur_name, fl_get_cursor_byname( *n ) );

    if ( c )
        c->timeout = timeout > 0 ? timeout : 20;

    return user_cur_name++;
}
