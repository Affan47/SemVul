on_import_biblio_apply_clicked (GtkWidget* widget, void* user) {
    gchar* basename = NULL;
    gchar* root_path = NULL;
    gchar* relative_path = NULL;

    const gchar* filename = gtk_entry_get_text (g_importgui->biblio_file);

    if ((filename) && (strlen(filename) != 0)) {
        if (g_active_editor->filename)
            root_path = g_path_get_dirname (g_active_editor->filename);
        relative_path = utils_path_to_relative (root_path, filename);
        editor_insert_bib (g_active_editor, relative_path);
        basename = g_path_get_basename (filename);
        gtk_label_set_text (gummi->biblio->filenm_label, basename);
        g_free (relative_path);
        g_free (root_path);
        g_free (basename);
        gtk_entry_set_text (g_importgui->biblio_file, "");
    }
    importgui_remove_all_panels ();
}
