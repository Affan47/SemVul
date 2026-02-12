Item *Item_cache::safe_charset_converter(CHARSET_INFO *tocs)
{
  if (!example)
    return Item::safe_charset_converter(tocs);
  Item *conv= example->safe_charset_converter(tocs);
  if (conv == example)
    return this;
  Item_cache *cache;
  if (!conv || conv->fix_fields(current_thd, (Item **) NULL) ||
      !(cache= new Item_cache_str(conv)))
    return NULL;
  cache->setup(conv);
  cache->fixed= false;
  return cache;
}
