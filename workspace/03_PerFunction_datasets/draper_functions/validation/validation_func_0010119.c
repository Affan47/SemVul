gnc_search_callback_button_execute (GNCSearchCallbackButton *cb,
                                    GNCSearchWindow *sw)
{
    GNCQueryView     *qview = GNC_QUERY_VIEW(sw->result_view);
    GtkTreeSelection *selection;
    GtkTreeModel     *model;
    GtkTreeIter       iter;


    g_assert(qview);
    selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(qview));
    g_assert(gtk_tree_selection_get_mode(selection) == GTK_SELECTION_MULTIPLE);
    selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(qview));


    if (cb->cb_multiselect_fn && (!cb->cb_fcn ))
    {


        sw->selected_item_list = g_list_reverse(sw->selected_item_list);


        (cb->cb_multiselect_fn)(sw->selected_item_list, sw->user_data);
    }
    else
    {

        if (cb->cb_fcn)
            (cb->cb_fcn)(&(sw->selected_item), sw->user_data);
    }
}
