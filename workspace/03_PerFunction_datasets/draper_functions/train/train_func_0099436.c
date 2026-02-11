gt_feature_index_gfflike_save_del(void *key, GT_UNUSED void *val,
                                             void *data, GtError *err)
{
  GtFeatureNode *fn = (GtFeatureNode*) key;
  GtFeatureNodeIterator *it;
  unsigned long *id;
  ObserverCallbackInfo *oci = (ObserverCallbackInfo*) data;
  int had_err = 0;

  it = gt_feature_node_iterator_new(fn);
  id = node_ul_gt_hashmap_get(oci->fis->cache_node2id, fn);
  if (!id) {
    return 0;
  }

  while ((fn = gt_feature_node_iterator_next(it))) {
    id = node_ul_gt_hashmap_get(oci->fis->cache_node2id, fn);
    remove_node_by_id(oci->fis, *id, err);
  }
  return had_err;
}
