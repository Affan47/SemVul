gnac_file_list_selection_changed_cb(GtkTreeSelection *selection,
                                    gpointer          user_data)
{
  gint selected_rows = gnac_file_list_count_selected_rows();

  if (selected_rows != 0 && state == GNAC_AUDIO_READY_STATE) {
    gnac_bars_activate_remove(TRUE);
  }

  gnac_bars_activate_properties(selected_rows == 1);
}
