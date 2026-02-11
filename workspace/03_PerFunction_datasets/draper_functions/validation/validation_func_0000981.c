Browser_List_Select_File_By_Iter_String (const gchar* stringIter, gboolean select_it)
{
    GtkTreeIter iter;
    ET_File *current_etfile = NULL;

    g_return_val_if_fail (fileListModel != NULL || BrowserList != NULL, NULL);

    if (gtk_tree_model_get_iter_from_string(GTK_TREE_MODEL(fileListModel), &iter, stringIter))
    {
        gtk_tree_model_get(GTK_TREE_MODEL(fileListModel), &iter,
                           LIST_FILE_POINTER, &current_etfile, -1);

        if (select_it)
        {
            GtkTreeSelection *selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(BrowserList));


            if (selection)
            {

                gtk_tree_selection_select_iter(selection, &iter);

            }
        }
        Browser_List_Set_Row_Visible(GTK_TREE_MODEL(fileListModel), &iter);
    }

    return current_etfile;
}
