diplomat_keep_moving_callback(GtkWidget *w, gpointer data)
{
  struct unit *punit;
  struct city *pcity;

  if ((punit = game_unit_by_number(diplomat_id))
      && (pcity = game_city_by_number(diplomat_target_id))
      && !same_pos(unit_tile(punit), city_tile(pcity))) {
    request_diplomat_action(DIPLOMAT_MOVE, diplomat_id,
                            diplomat_target_id, 0);
  }
  gtk_widget_destroy(diplomat_dialog);
}
