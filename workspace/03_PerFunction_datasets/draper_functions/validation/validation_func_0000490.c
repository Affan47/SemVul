get_label(struct st_translate *t, unsigned branch_target)
{
   unsigned i;

   if (t->labels_count + 1 >= t->labels_size) {
      t->labels_size = 1 << (util_logbase2(t->labels_size) + 1);
      t->labels = (struct label *)realloc(t->labels,
                                          t->labels_size * sizeof(struct label));
      if (t->labels == NULL) {
         static unsigned dummy;
         t->error = TRUE;
         return &dummy;
      }
   }

   i = t->labels_count++;
   t->labels[i].branch_target = branch_target;
   return &t->labels[i].token;
}
