Mask_Editor_List_Duplicate (void)
{
    gchar *text = NULL;
    GList *selectedRows;
    GList *l;
    GList *toInsert = NULL;
    GtkTreeSelection *selection;
    GtkTreeIter rowIter;
    GtkTreeModel *treeModel;

    g_return_if_fail (MaskEditorList != NULL);

    selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(MaskEditorList));
    selectedRows = gtk_tree_selection_get_selected_rows(selection, NULL);
    treeModel = gtk_tree_view_get_model(GTK_TREE_VIEW(MaskEditorList));

    if (!selectedRows)
    {
        Log_Print(LOG_ERROR,_("Copy: No row selected"));
        return;
    }


    for (l = selectedRows; l != NULL; l = g_list_next (l))
    {
        if (gtk_tree_model_get_iter (treeModel, &rowIter,
                                     (GtkTreePath*)l->data))
        {
            gtk_tree_model_get(treeModel, &rowIter, MASK_EDITOR_TEXT, &text, -1);
            toInsert = g_list_prepend (toInsert, text);
        }
    }

    for (l = toInsert; l != NULL; l = g_list_next (l))
    {
        gtk_list_store_insert_with_values (GTK_LIST_STORE(treeModel), &rowIter,
                                           0, MASK_EDITOR_TEXT,
                                           (gchar *)l->data, -1);
    }


    if (toInsert)
        Mask_Editor_List_Set_Row_Visible(treeModel,&rowIter);


    g_list_free_full (selectedRows, (GDestroyNotify)gtk_tree_path_free);
    g_list_free_full (toInsert, (GDestroyNotify)g_free);
}
