sgf_addCSElem(Sgf *mc, SgfType type,
			  GoStone c, const char *s)  {
  SgfElem  *se;

  if (type == sgfType_comment)  {
    se = sgfElem_findTypeInNode(mc->active, sgfType_comment);
    if (se)  {
      str_copyChars(se->sVal, s);
      return;
    }
  }
  sgf_addCElem(mc, type, c);
  mc->active->sVal = str_createChars(s);
}
