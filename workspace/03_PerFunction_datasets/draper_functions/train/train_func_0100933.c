insert_ln ( LIST * l, LISTNODE * ln, void * data_ptr )
{
  LISTNODE * lnptr;

  CKLMAGIC(l);

  if (ln==NULL) {
    ladd ( l, data_ptr );
    CKLMAGIC(l);
    return 0;
  }

  lnptr = get_listnode(l);
  if (lnptr == NULL) {
#ifdef BOS
    breakpoint();
#endif
    return -1;
  }

  CKMAGIC(lnptr);

  lnptr->data = data_ptr;

  if (ln==l->top) {


    lnptr->next = ln;
    lnptr->prev = NULL;
    ln->prev = lnptr;
    l->top = lnptr;
  }
  else if (ln==NULL) {


    lnptr->next = NULL;
    lnptr->prev = l->bottom;
    l->bottom->next = lnptr;
    l->bottom = lnptr;
  }
  else {


    lnptr->next = ln;
    lnptr->prev = ln->prev;
    lnptr->next->prev = lnptr;
    lnptr->prev->next = lnptr;
  }

  l->num++;

  CKLMAGIC(l);

  return 0;
}
