flush_hash_table (void)
{
  int i;
  struct table_elt *p;

  for (i = 0; i < HASH_SIZE; i++)
    for (p = table[i]; p; p = table[i])
      {


	if (REG_P (p->exp))
	  invalidate (p->exp, VOIDmode);
	else
	  remove_from_table (p, i);
      }
}
