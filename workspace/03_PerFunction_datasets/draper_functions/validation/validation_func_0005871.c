util_hash_insert(struct util_hash *hash, unsigned key, void *data)
{
   util_data_might_grow(hash->data.d);

   {
      struct util_node **nextNode = util_hash_find_node(hash, key);
      struct util_node *node = util_hash_create_node(hash, key, data, nextNode);
      if (!node) {
         struct util_hash_iter null_iter = {hash, 0};
         return null_iter;
      }

      {
         struct util_hash_iter iter = {hash, node};
         return iter;
      }
   }
}
