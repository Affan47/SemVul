cull_hash_delete_non_unique_chain(htable table, const void *key,
                                       const void **data)
{
   non_unique_header *head = (non_unique_header *)*data;
   if (head != NULL) {
      non_unique_hash *nuh = head->first;
      while(nuh != NULL) {
         non_unique_hash *del = nuh;
         nuh = nuh->next;
         free(del);
      }
      free(head);
   }
}
