simple_cs_init_functions(CHARSET_INFO *cs)
{
  if (cs->state & MY_CS_BINSORT)
    cs->coll= &my_collation_8bit_bin_handler;
  else
    cs->coll= &my_collation_8bit_simple_ci_handler;

  cs->cset= &my_charset_8bit_handler;
}
