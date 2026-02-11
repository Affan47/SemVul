fl_get_formbrowser_topform( FL_OBJECT * ob )
{
    int topline = 0;
    FLI_FORMBROWSER_SPEC *sp = ob->spec;

    if ( ! IsFormBrowserClass( ob ) )
        M_err( "fl_get_formbrowser_topform", "%s not a formbrowser",
               ob ? ob->label : "null" );
    else
        topline = sp->top_form + 1;

    return topline ? sp->form[ topline - 1 ] : 0;
}
