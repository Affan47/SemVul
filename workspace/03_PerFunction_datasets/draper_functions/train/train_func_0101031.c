clear_suppress(struct dscan_state *ds, int sd)
{
  int i;
  struct dscan_sup *dsp_src, *dsp_dst;

  if (sd == 0) {
    for (i = 0; i < DSCAN_HASHSIZE; ++i) {
      while (ds->hash_sup_src[i].slh_first != NULL) {
        dsp_src = ds->hash_sup_src[i].slh_first;
        FT_SLIST_REMOVE_HEAD(&ds->hash_sup_src[i], chain);
        free (dsp_src);
      }
    }
  }

  if (sd == 1) {
    for (i = 0; i < DSCAN_HASHSIZE; ++i) {
      while (ds->hash_sup_dst[i].slh_first != NULL) {
        dsp_dst = ds->hash_sup_dst[i].slh_first;
        FT_SLIST_REMOVE_HEAD(&ds->hash_sup_dst[i], chain);
        free (dsp_dst);
      }
    }
  }

}
