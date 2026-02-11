fl_set_positioner_ybounds( FL_OBJECT * ob,
                           double      min,
                           double     max )
{
    FLI_POSITIONER_SPEC *sp = ob->spec;

    if ( sp->ymin != min || sp->ymax != max )
    {
        sp->ymin = min;
        sp->ymax = max;
        sp->yval = fli_clamp( sp->yval, sp->ymin, sp->ymax );
        fl_redraw_object( ob );
    }
}
