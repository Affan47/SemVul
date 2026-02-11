print_tree_view_list_draw_page ( GtkPrintOperation *operation,
                        GtkPrintContext *context,
                        gint page,
                        gpointer data )
{
    GtkTreeView *tree_view = ( GtkTreeView * ) data;
    gint line_position = 0;

    devel_debug_int (page);


    if ( !page && title_string && strlen ( title_string ) )
        line_position = print_tree_view_list_draw_title ( context, line_position );


    if ( gsb_data_print_config_get_draw_columns_name () )
        line_position = print_tree_view_list_draw_columns_title ( context, line_position, tree_view );


    line_position = print_tree_view_list_draw_rows_data ( context, line_position, tree_view, page );

    return FALSE;
}
