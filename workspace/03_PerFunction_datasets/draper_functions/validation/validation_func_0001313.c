gt_strgraph_nofedges_Edgenum(
    const GtStrgraph *strgraph)
{
  GtStrgraphVnum i;
  GtStrgraphEdgenum total_degree = 0;
  gt_assert(strgraph != NULL);
  for (i = 0; i < GT_STRGRAPH_NOFVERTICES(strgraph); i++)
    total_degree += GT_STRGRAPH_V_OUTDEG(strgraph, i);
  return total_degree;
}
