p_file_entry_update_callback(GtkWidget *widget,
                   fmac_globalparams_t *gpp)
{
 if(gpp)
 {
   g_snprintf(gpp->filtermacro_file, sizeof(gpp->filtermacro_file), "%s"
             , gtk_entry_get_text(GTK_ENTRY(widget))
             );
   p_tree_fill (gpp);
 }
}
