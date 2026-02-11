on_cme__entry_debug_flat_changed       (GtkEditable     *editable,
                                        GapCmeGlobalParams *gpp)
{
  GtkEntry *entry;

 if(gap_debug) printf("CB: on_cme__entry_debug_flat_changed\n");
 if(gpp == NULL) return;

 entry = GTK_ENTRY(gpp->cme__entry_debug_flat);
 if(entry)
 {
    char *l_write_to;

    l_write_to = g_strdup(gtk_entry_get_text(entry));

    if(gap_debug) printf("on_cme__entry_debug_multi_changed:l_write_to:%s:\n", l_write_to);
    gimp_set_data( GAP_VID_ENC_SAVE_FLAT, l_write_to, strlen(l_write_to) +1);
    g_free(l_write_to);
 }

}
