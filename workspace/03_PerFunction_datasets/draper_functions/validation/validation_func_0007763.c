util_hash_table_get(struct util_hash_table *ht,
                    void *key)
{
   unsigned key_hash;
   struct util_hash_table_item *item;

   assert(ht);
   if (!ht)
      return NULL;

   key_hash = ht->hash(key);

   item = util_hash_table_find_item(ht, key, key_hash);
   if(!item)
      return NULL;

   return item->value;
}
