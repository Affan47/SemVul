player_should_be_shown(const struct player *pplayer)
{
  return NULL != pplayer && (player_dlg_show_dead_players
                             || pplayer->is_alive)
         && (!is_barbarian(pplayer));
}
