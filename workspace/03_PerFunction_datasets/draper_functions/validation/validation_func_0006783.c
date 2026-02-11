conn_menu_player_take(GObject *object, gpointer data)
{
  struct player *pplayer;

  if (object_extract(object, &pplayer, NULL)) {
    client_take_player(pplayer);
  }
}
