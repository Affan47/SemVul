reset_all_start_commands(void)
{
  if (S_S_INITIAL != server_state()) {
    return;
  }
  players_iterate(pplayer) {
    if (pplayer->is_ready) {
      pplayer->is_ready = FALSE;
      send_player_info_c(pplayer, game.est_connections);
    }
  } players_iterate_end;
}
