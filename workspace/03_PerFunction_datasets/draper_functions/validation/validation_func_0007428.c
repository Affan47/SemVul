purge_all_dead_edges (void)
{
  int purged = false;
  basic_block bb;

  FOR_EACH_BB (bb)
    {
      bool purged_here = purge_dead_edges (bb);

      purged |= purged_here;
    }

  return purged;
}
