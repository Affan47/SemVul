fl_set_object_position( FL_OBJECT * obj,
                        FL_Coord    x,
                        FL_Coord    y )
{
    int visible = obj->visible;
    double diff;

    if ( obj->x == x && obj->y == y )
        return;

    if ( fli_inverted_y )
        y = obj->form->h - obj->h - y;

    if ( obj->x == x && obj->y == y )
        return;

    if ( visible )
        fl_hide_object( obj );

    if ( x != obj->x )
    {
        diff = x - obj->fl1;
        obj->fl1 += diff;
        obj->fl2 += diff;
        obj->fr1 -= diff;
        obj->fr2 -= diff;
        obj->x = x;
    }

    if ( y != obj->y )
    {
        diff = y - obj->ft1;
        obj->ft1 += diff;
        obj->ft2 += diff;
        obj->fb1 -= diff;
        obj->fb2 -= diff;
        obj->y = y;
    }

    if ( fli_inverted_y )
        obj->y = TRANY( obj, obj->form );

    if ( ! obj->parent )
        fli_recalc_intersections( obj->form );

    if ( visible )
    {
        fli_handle_object( obj, FL_MOVEORIGIN, 0, 0, 0, NULL, 0 );
        fl_show_object( obj );
    }
}
