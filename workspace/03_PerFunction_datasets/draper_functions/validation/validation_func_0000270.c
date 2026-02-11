menu_tab_close(void)
{
    gtk_notebook_remove_page((GtkNotebook *) mainnotebook, ViewedTabNum);

    logxy[ViewedTabNum][0] = FALSE;
    logxy[ViewedTabNum][1] = FALSE;

    zoomareabox[ViewedTabNum] = NULL;
    logbox[ViewedTabNum] = NULL;
    oppropbox[ViewedTabNum] = NULL;

    NoteBookNumPages--;

    if (NoteBookNumPages == 0) gtk_action_group_set_sensitive(tab_action_group, FALSE);

  return NULL;
}
