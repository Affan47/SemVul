fl_replace_choice( FL_OBJECT *  ob,
                   int          numb,
                   const char * str )
{
    FLI_CHOICE_SPEC *sp = ob->spec;

    if ( numb < 1 || numb > sp->numitems )
        return;

    if ( sp->items[ numb ] )
        fl_free( sp->items[ numb ] );
    sp->items[ numb ] = fl_strdup( str );

    if ( sp->val == numb )
        fl_redraw_object( ob );
}
