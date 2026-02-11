int_term(struct term *t)
{
  int i;
  return(t->type == NAME && str_int(sn_to_str(t->sym_num),&i) && i>=0);
}
