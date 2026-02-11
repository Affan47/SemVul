fl_set_nmenu_hl_text_color(FL_OBJECT * obj,
                           FL_COLOR    color )
{
    FLI_NMENU_SPEC *sp;
    FL_COLOR old_color;

    if ( obj == NULL )
    {
        M_err( "fl_set_nmenu_hl_text_color", "NULL object" );
        return FL_MAX_COLORS;
    }

    if ( color >= FL_MAX_COLORS )
    {
        M_err( "fl_set_nmenu_hl_text_color", "Invalid color argument" );
        return FL_MAX_COLORS;
    }

    sp = obj->spec;

    old_color = sp->hl_color;
    sp->hl_color = color;
    fl_redraw_object( obj );

    return old_color;
}
