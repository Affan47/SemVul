ET_Display_Filename_To_UI (ET_File *ETFile)
{
    gchar *pos;
    gchar *new_filename_utf8;
    gchar *basename_utf8;
    gchar *dirname_utf8;
    gchar *text;

    g_return_if_fail (ETFile != NULL);

    new_filename_utf8 = ((File_Name *)((GList *)ETFile->FileNameNew)->data)->value_utf8;


    basename_utf8 = g_path_get_basename(new_filename_utf8);


    if ((pos=g_utf8_strrchr(basename_utf8, -1, '.'))!=NULL)
        *pos = 0;
    gtk_entry_set_text(GTK_ENTRY(FileEntry),basename_utf8);


    g_free(basename_utf8);

    gtk_editable_set_position(GTK_EDITABLE(FileEntry),0);


    dirname_utf8 = g_path_get_dirname(new_filename_utf8);
    Browser_Entry_Set_Text(dirname_utf8);


    text = g_strdup_printf(ngettext("One file","%u files",ET_Get_Number_Of_Files_In_Directory(dirname_utf8)),ET_Get_Number_Of_Files_In_Directory(dirname_utf8));
    Browser_Label_Set_Text(text);
    g_free(dirname_utf8);
    g_free(text);
}
