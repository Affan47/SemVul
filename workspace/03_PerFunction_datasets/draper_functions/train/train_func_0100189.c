gt_disc_distri_show(const GtDiscDistri *d, GtFile *outfp)
{
  GtShowValueInfo showvalueinfo;
  GT_UNUSED int rval;

  gt_assert(d);

  if (d->hashdist != NULL) {
    showvalueinfo.cumulative_probability = 0.0;
    showvalueinfo.num_of_occurrences = d->num_of_occurrences;
    showvalueinfo.outfp = outfp;
    rval = ul_ull_gt_hashmap_foreach_in_default_order(d->hashdist, showvalue,
                                                      &showvalueinfo, NULL);
    gt_assert(!rval);
  }
}
