fl_get_focus_object( FL_FORM * form )
{
    FL_OBJECT *fo = NULL;;

    if ( form && ( fo = form->focusobj ) )
        while ( fo->parent )
            fo = fo->parent;

    return fo;
}
