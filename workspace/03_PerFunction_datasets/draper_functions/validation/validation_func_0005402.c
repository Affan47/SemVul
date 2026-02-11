_on_st_dnd_get_track_foreach(GtkTreeModel *tm, GtkTreePath *tp, GtkTreeIter *i, gpointer data) {
    GList *gl;
    TabEntry *entry = NULL;
    GString *tracklist = (GString *) data;

    g_return_if_fail (tracklist);

    gtk_tree_model_get(tm, i, ST_COLUMN_ENTRY, &entry, -1);
    g_return_if_fail (entry);


    for (gl = entry->members; gl; gl = gl->next) {
        Track *tr = gl->data;
        g_return_if_fail (tr);
        g_string_append_printf(tracklist, "%p\n", tr);
    }
}
