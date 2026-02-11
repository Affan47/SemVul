count_stealable_techs(struct player *pplayer, struct player *tplayer)
{
  int count = 0;

  advance_index_iterate(A_FIRST, index) {
    if ((player_invention_state(pplayer, index) != TECH_KNOWN)
        && (player_invention_state(tplayer, index) == TECH_KNOWN)) {
      count++;
    }
  } advance_index_iterate_end;

  return count;
}
