fl_set_input_return( FL_OBJECT    * obj,
                     unsigned int   when )
{
    FLI_INPUT_SPEC *sp = obj->spec;

    if ( when & FL_RETURN_END_CHANGED )
        when &= ~ ( FL_RETURN_END | FL_RETURN_CHANGED );

    obj->how_return = sp->input->how_return = when;
    fl_set_object_return( sp->vscroll, FL_RETURN_CHANGED );
    fl_set_object_return( sp->hscroll, FL_RETURN_CHANGED );
}
