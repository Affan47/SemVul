gt_encseq_options_register_loading(GtOptionParser *op,
                                                    GtStr *indexname)
{
  gt_assert(op != NULL);
  return gt_encseq_options_register_generic(op,
                                            GT_ENCSEQ_OPTS_LOAD,
                                            indexname,
                                            NULL);
}
