gt_md5set_alloc_table(GtMD5Set *set, unsigned long newsize)
{
  gt_md5_t *oldtable;
  unsigned long oldsize;

  oldsize = set->alloc;
  oldtable = set->table;
  set->alloc = newsize;
  set->maxfill =
    (unsigned long)((double)newsize * GT_MD5SET_MAX_LOAD_FACTOR);
  set->table = gt_calloc((size_t)newsize, sizeof (gt_md5_t));
  if (oldtable != NULL)
  {
    gt_log_log("rehashing %lu elements; old size: %lu, new size: %lu\n",
        set->fill, oldsize, newsize);
    gt_md5set_rehash(set, oldtable, oldsize);
    gt_free(oldtable);
  }
}
