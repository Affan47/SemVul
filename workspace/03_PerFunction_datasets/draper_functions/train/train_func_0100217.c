cso_hash_take(struct cso_hash *hash,
                      unsigned akey)
{
   struct cso_node **node = cso_hash_find_node(hash, akey);
   if (*node != hash->data.e) {
      void *t = (*node)->value;
      struct cso_node *next = (*node)->next;
      cso_free_node(*node);
      *node = next;
      --hash->data.d->size;
      cso_data_has_shrunk(hash->data.d);
      return t;
   }
   return 0;
}
