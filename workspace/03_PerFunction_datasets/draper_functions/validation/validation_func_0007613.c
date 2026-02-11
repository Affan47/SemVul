add(SimpleString word, ObjStack & buf) const
{
  unsigned int cond;

  if ((word.size > stripl) && (word.size >= conds->num)) {
    const byte * cp = (const byte *) word.str;
    for (cond = 0;  cond < conds->num;  cond++) {
      if ((conds->get(*cp++) & (1 << cond)) == 0)
        break;
    }
    if (cond >= conds->num) {

      int alen = word.size - stripl;
      char * newword = (char *)buf.alloc(alen + appndl + 1);
      if (appndl) memcpy(newword, appnd, appndl);
      memcpy(newword + appndl, word + stripl, alen + 1);
      return SimpleString(newword, alen + appndl);
    }
  }
  return SimpleString();
}
