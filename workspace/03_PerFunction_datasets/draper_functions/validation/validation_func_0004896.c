mp3(game *g, player *p, item *it, bool t)
{
 if (it->charges == 0)
  g->add_msg("The mp3 player's batteries are dead.");
 else if (p->has_active_item(itm_mp3_on))
  g->add_msg("You are already listening to an mp3 player!");
 else {
  g->add_msg("You put in the earbuds and start listening to music.");
  it->make(g->itypes[itm_mp3_on]);
  it->active = true;
 }
}
