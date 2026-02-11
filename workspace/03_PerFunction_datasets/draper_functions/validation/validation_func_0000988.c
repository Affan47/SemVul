get_allied_with_enemy_player(const struct player *us,
                             const struct player *them)
{
  players_iterate_alive(aplayer) {
    if (aplayer != us
        && aplayer != them
        && pplayers_allied(them, aplayer)
        && player_diplstate_get(us, aplayer)->type == DS_WAR) {
      return aplayer;
    }
  } players_iterate_alive_end;
  return NULL;
}
