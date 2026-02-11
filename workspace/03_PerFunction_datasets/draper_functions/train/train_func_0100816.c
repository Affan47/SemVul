feature_node_iterator_new_base(const GtFeatureNode
                                                             *fn)
{
  GtFeatureNodeIterator *fni;
  gt_assert(fn);
  fni = gt_malloc(sizeof *fni);
  fni->fn = (GtFeatureNode*) gt_genome_node_ref((GtGenomeNode*) fn);
  fni->feature_stack = gt_array_new(sizeof (GtFeatureNode*));
  return fni;
}
