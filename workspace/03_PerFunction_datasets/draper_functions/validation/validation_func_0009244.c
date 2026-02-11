on_wp_filesel_button_OK_clicked      (GtkButton         *button
                                     ,GapMorphGUIParams *mgup)
{
  const gchar *filename;
  gint   l_errno;

 if(gap_debug) printf("CB: on_wp_filesel_button_OK_clicked\n");
 if(mgup == NULL) return;
 if(mgup->workpoint_file_ptr == NULL) return;


 if(mgup->shell == NULL) { gtk_main_quit (); return; }


 if(mgup->wp_filesel)
 {
   filename =  gtk_file_selection_get_filename (GTK_FILE_SELECTION (mgup->wp_filesel));
   g_snprintf(mgup->workpoint_file_ptr
                ,GAP_MORPH_WORKPOINT_FILENAME_MAX_LENGTH
                ,"%s"
                ,filename
                );
   if(mgup->wp_save_mode)
   {
     gboolean l_wr_permission;

     l_wr_permission = gap_arr_overwrite_file_dialog(filename);


     if(mgup->shell == NULL) { gtk_main_quit (); return; }

     if(l_wr_permission)
     {
       if(!gap_moprh_exec_save_workpointfile(filename, mgup))
       {
         l_errno = errno;
         g_message (_("Failed to write morph workpointfile\n"
                      "filename: '%s':\n%s")
                   , filename
                   , g_strerror (l_errno)
                   );
       }
     }
   }
   else
   {
     GapMorphWorkPoint *wp_list;

     wp_list = gap_moprh_exec_load_workpointfile(filename, mgup);
     l_errno = errno;
     if(wp_list)
     {
       if(mgup->mgpp->master_wp_list)
       {
         gap_morph_exec_free_workpoint_list(&mgup->mgpp->master_wp_list);
       }
       mgup->mgpp->master_wp_list = wp_list;
       p_set_current_workpoint(&mgup->src_win, mgup->mgpp->master_wp_list);
       p_refresh_total_points_label(mgup);
       p_upd_widget_values(mgup);
     }
     else
     {
       if(l_errno != 0)
       {
         g_message(_("ERROR: Could not open morph workpoints\n"
                   "filename: '%s'\n%s")
                  ,filename, g_strerror (errno));
       }
       else
       {
         g_message(_("ERROR: Could not read morph workpoints\n"
                   "filename: '%s'\n(Is not a valid morph workpoint file)")
                  ,filename);
       }
     }
   }

   on_wp_filesel_button_cancel_clicked(NULL, (gpointer)mgup);
 }
}
