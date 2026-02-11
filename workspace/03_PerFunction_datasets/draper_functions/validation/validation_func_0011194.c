trans_retrieve(uint64 key, int * move, int * min_depth, int * max_depth, int * min_value, int * max_value, int * eval, bool refresh) {

   entry_t * entry;
   int i;

   ASSERT(move!=NULL);
   ASSERT(min_depth!=NULL);
   ASSERT(max_depth!=NULL);
   ASSERT(min_value!=NULL);
   ASSERT(max_value!=NULL);
   ASSERT(eval!=NULL);
   ASSERT(refresh==true||refresh==false);


   if (UseStats) Trans->read_nb++;


   entry = trans_entry(key);

   for (i = 0; i < ClusterSize; i++, entry++) {

      if (entry->lock == KEY_LOCK(key)) {


         if (UseStats) Trans->read_hit++;
         if (refresh && entry->date != Trans->date) entry->date = Trans->date;

         *move = entry->move;
         *eval = entry->eval;

         *min_depth = entry->min_depth;
         *max_depth = entry->max_depth;
         *min_value = entry->min_value;
         *max_value = entry->max_value;

         return true;
      }
   }


   return false;
}
