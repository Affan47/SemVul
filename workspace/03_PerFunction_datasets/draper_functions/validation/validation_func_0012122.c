hwloc_bitmap_dup(const struct hwloc_bitmap_s * old)
{
  struct hwloc_bitmap_s * new;

  if (!old)
    return NULL;

  HWLOC__BITMAP_CHECK(old);

  new = malloc(sizeof(struct hwloc_bitmap_s));
  if (!new)
    return NULL;

  new->ulongs = malloc(old->ulongs_allocated * sizeof(unsigned long));
  if (!new->ulongs) {
    free(new);
    return NULL;
  }
  new->ulongs_allocated = old->ulongs_allocated;
  new->ulongs_count = old->ulongs_count;
  memcpy(new->ulongs, old->ulongs, new->ulongs_count * sizeof(unsigned long));
  new->infinite = old->infinite;
#ifdef HWLOC_DEBUG
  new->magic = HWLOC_BITMAP_MAGIC;
#endif
  return new;
}
