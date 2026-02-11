dbg_cnt_list_all_counters (void)
{
  int i;
  printf ("  %-30s %-5s %-5s\n", "counter name",  "limit", "value");
  printf ("----------------------------------------------\n");
  for (i = 0; i < debug_counter_number_of_counters; i++)
    printf ("  %-30s %5d %5u\n",
            map[i].name, limit[map[i].counter], count[map[i].counter]);
  printf ("\n");
}
