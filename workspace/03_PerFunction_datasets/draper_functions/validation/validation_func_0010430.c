_new_KeyTab(void)
{
  KeyTab *kt;


  kt = (KeyTab *) malloc(sizeof(KeyTab));
  if(!kt) {
    errno = ENOMEM;
    return NULL;
  };


  kt->err = NULL;
  kt->size = KT_TABLE_INC;
  kt->nkey = 0;
  kt->table = NULL;
  kt->actions = NULL;
  kt->smem = NULL;


  kt->err = _new_ErrMsg();
  if(!kt->err)
    return _del_KeyTab(kt);


  kt->table = (KeySym *) malloc(sizeof(kt->table[0]) * kt->size);
  if(!kt->table) {
    errno = ENOMEM;
    return _del_KeyTab(kt);
  };


  kt->actions = _new_HashTable(NULL, KT_HASH_SIZE, IGNORE_CASE, NULL, 0);
  if(!kt->actions)
    return _del_KeyTab(kt);


  kt->smem = _new_StringMem(KT_TABLE_INC);
  if(!kt->smem)
    return _del_KeyTab(kt);
  return kt;
}
