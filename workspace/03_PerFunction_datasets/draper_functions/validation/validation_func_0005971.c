gt_strgraph_sort_edges_by_len(GtStrgraph *strgraph, bool show_progressbar)
{
  GtStrgraphVnum i;
  unsigned long long progress = 0;

  gt_assert(strgraph != NULL);

  if (show_progressbar)
    gt_progressbar_start(&progress,
        (unsigned long long)GT_STRGRAPH_NOFVERTICES(strgraph));

  for (i = 0; i < GT_STRGRAPH_NOFVERTICES(strgraph); i++)
  {
    GT_STRGRAPH_SORT_V_EDGES(strgraph, i);
    if (show_progressbar)
      progress++;
  }

  strgraph->state = GT_STRGRAPH_SORTED_BY_L;

  if (show_progressbar)
    gt_progressbar_stop();
}
