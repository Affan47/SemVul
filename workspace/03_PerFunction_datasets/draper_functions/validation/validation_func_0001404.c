board(game *g, monster *z, int x, int y)
{
 int t;
 if (g->u_see(z, t))
  g->add_msg("The %s steps on a spiked board!", z->name().c_str());
 if (z->hurt(rng(6, 10)))
  g->kill_mon(g->mon_at(x, y));
 else
  z->moves -= 80;
}
