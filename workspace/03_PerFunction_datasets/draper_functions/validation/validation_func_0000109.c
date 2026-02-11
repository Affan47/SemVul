p_pw_fmac_filesel_button_cb ( GtkWidget *w
                       , GapStbPropWidget *pw)
{
  GtkWidget *filesel = NULL;

  if(pw->scene_detection_busy)
  {
     return;
  }

  if(pw->pw_fmac_filesel != NULL)
  {
     gtk_window_present(GTK_WINDOW(pw->pw_fmac_filesel));
     return;
  }
  if(pw->stb_elem_refptr == NULL) { return; }

  filesel = gtk_file_selection_new ( _("Set Filtermacro Filename"));
  pw->pw_fmac_filesel = filesel;

  gtk_window_set_position (GTK_WINDOW (filesel), GTK_WIN_POS_MOUSE);
  g_signal_connect (GTK_FILE_SELECTION (filesel)->ok_button,
                    "clicked", G_CALLBACK (p_pw_fmac_filesel_pw_ok_cb),
                    pw);
  g_signal_connect (GTK_FILE_SELECTION (filesel)->cancel_button,
                    "clicked", G_CALLBACK (p_pw_fmac_filesel_pw_close_cb),
                    pw);
  g_signal_connect (filesel, "destroy",
                    G_CALLBACK (p_pw_fmac_filesel_pw_close_cb),
                    pw);


  if(pw->stb_elem_refptr->filtermacro_file)
  {
    gtk_file_selection_set_filename (GTK_FILE_SELECTION (filesel),
                                     pw->stb_elem_refptr->filtermacro_file);
  }
  gtk_widget_show (filesel);

}
