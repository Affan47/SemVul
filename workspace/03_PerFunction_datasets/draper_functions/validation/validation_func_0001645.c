finish_confid()
{
  fprintf (cid,"\t.\n");
  fprintf (cid,"\n");
  dump_variants (cid);
  dump_rules (cid);
  free_rlist_entries ();
  if (rule_list) free (rule_list);
  rlist_size = 0;
  rlist_level = 0;
}
