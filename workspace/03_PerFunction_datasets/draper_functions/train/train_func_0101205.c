lookup_or_add_counter (htab_t hash, const char *id, int val,
		       bool histogram_p)
{
  statistics_counter_t **counter;
  statistics_counter_t c;
  c.id = id;
  c.val = val;
  counter = (statistics_counter_t **) htab_find_slot (hash, &c, INSERT);
  if (!*counter)
    {
      *counter = XNEW (struct statistics_counter_s);
      (*counter)->id = xstrdup (id);
      (*counter)->val = val;
      (*counter)->histogram_p = histogram_p;
      (*counter)->prev_dumped_count = 0;
      (*counter)->count = 0;
    }
  return *counter;
}
