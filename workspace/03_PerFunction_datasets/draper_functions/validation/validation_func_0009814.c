change_menu_item_cb( FL_OBJECT * ob,
                     long        data  FL_UNUSED_ARG )
{
    FD_menuattrib *ui = ob->form->fdui;
    int i = fl_get_browser( ui->content_br );
    FL_OBJECT *edited = ui->vdata;
    FLI_MENU_SPEC *sp = edited->spec;

    if ( i > 0 )
    {
        fl_set_input( ui->input, fl_get_browser_line( ui->content_br, i ) );

        if ( sp->shortcut[ i ] )
            fl_set_input( ui->shortcut, sp->shortcut[ i ] );

        fl_set_choice_text( ui->mode, get_pupmode_name( sp->mode[ i ] ) + 3 );

        if ( sp->cb[ i ] )
            fl_set_input( ui->item_cb, ( char * ) sp->cb[ i ] );
        else
            fl_set_input( ui->item_cb, "" );

        fl_set_counter_value( ui->id, sp->mval[ i ] );
    }
}
