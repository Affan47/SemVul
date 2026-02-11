store_exon(GtFeatureNode *fn, void *data, GT_UNUSED GtError *err)
{
  StoreExonFeatureInfo *info = (StoreExonFeatureInfo*) data;
  GtRange range;
  gt_error_check(err);
  gt_assert(fn && info);
  if (gt_feature_node_has_type(fn, info->feature_type)) {
    range = gt_genome_node_get_range((GtGenomeNode*) fn);
    gt_array_add(info->exons, range);
  }
  return 0;
}
