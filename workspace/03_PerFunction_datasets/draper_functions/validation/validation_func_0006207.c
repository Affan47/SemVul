build_md5map(GtMD5Tab *md5_tab)
{
  unsigned long i;
  gt_assert(md5_tab);
  md5_tab->md5map = gt_hashmap_new(GT_HASH_STRING, NULL, NULL);
  for (i = 0; i < md5_tab->num_of_md5s; i++) {
    gt_hashmap_add(md5_tab->md5map, (void*) gt_md5_tab_get(md5_tab, i),
                   (void*) (i + 1));
  }
}
