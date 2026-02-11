cull_hash_insert(const lListElem *ep, void *key, cull_htable ht, bool unique)
{
   if(ht == NULL || ep == NULL || key == NULL) {
      return;
   }

   if (unique) {
      sge_htable_store(ht->ht, key, ep);
   } else {
      union {
         non_unique_header *l;
         void *p;
      } head;

      union {
         non_unique_hash *l;
         void *p;
      } nuh;

      head.l = NULL;
      nuh.l = NULL;


      if(sge_htable_lookup(ht->ht, key, (const void **) &head.p) == True) {

         if (sge_htable_lookup(ht->nuht, &ep, (const void **)&nuh.p) == False) {
            nuh.p = (non_unique_hash *)malloc(sizeof(non_unique_hash));
            nuh.l->data = ep;
            nuh.l->prev = head.l->last;
            nuh.l->next = NULL;
            nuh.l->prev->next = nuh.p;
            head.l->last = nuh.p;
            sge_htable_store(ht->nuht, &ep, nuh.p);
         }
      } else {
         head.p = (non_unique_header *)malloc(sizeof(non_unique_header));
         nuh.p = (non_unique_hash *)malloc(sizeof(non_unique_hash));
         head.l->first = nuh.p;
         head.l->last = nuh.p;
         nuh.l->prev = NULL;
         nuh.l->next = NULL;
         nuh.l->data = ep;
         sge_htable_store(ht->ht, key, head.p);
         sge_htable_store(ht->nuht, &ep, nuh.p);
      }
   }
}
