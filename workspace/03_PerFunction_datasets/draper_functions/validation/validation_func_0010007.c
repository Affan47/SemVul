Rd_Callable(WamWord start_word, int *func, int *arity)
{
  WamWord word, tag_mask;
  WamWord *adr;

  DEREF(start_word, word, tag_mask);

  if (tag_mask == TAG_ATM_MASK)
    {
      *func = UnTag_ATM(word);
      *arity = 0;
      return (WamWord *) arity;
    }

  if (tag_mask == TAG_LST_MASK)
    {
      adr = UnTag_LST(word);
      *func = ATOM_CHAR('.');
      *arity = 2;
      return &Car(adr);
    }

  if (tag_mask == TAG_STC_MASK)
    {
      adr = UnTag_STC(word);
      *func = Functor(adr);
      *arity = Arity(adr);
      return &Arg(adr, 0);
    }

  return NULL;
}
