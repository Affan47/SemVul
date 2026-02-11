lins_n ( LISTID lid, void * data_ptr, unsigned int n )
{
  int i;
  LIST * l;
  LISTNODE * ln;

  l = (LIST *)lid;

  CKLMAGIC(l);

  if ((n<1)||(n>(l->num+1))) {
    return -1;
  }

  if (l->num == 0) {
    return ladd ( lid, data_ptr );
  }


  ln = l->top;
  i = 1;
  while (ln && (i!=n)) {
    CKMAGIC(ln);
    ln = ln->next;
    i++;
  }

  if (!ln) {
    CKLMAGIC(l);
    return -1;
  }

  CKLMAGIC(l);


  return insert_ln ( l, ln, data_ptr );
}
