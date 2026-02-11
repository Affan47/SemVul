gt_feature_node_set_end(GtFeatureNode *fn, unsigned long end)
{
  gt_assert(fn && fn->range.start <= end);
  fn->range.end = end;
  if (fn->observer && fn->observer->range_changed)
    fn->observer->range_changed(fn, &(fn->range), fn->observer->data);
}
