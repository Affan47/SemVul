LC_Card_FindFile(LC_CARD *card,
                               const char *type,
                               const char *fname) {
  GWEN_XMLNODE *n;
  GWEN_XMLNODE *currDF;
  int isSameLevel;

  currDF=card->dfNode;
  if (!currDF)
    currDF=card->appNode;

  isSameLevel=1;
  while(currDF) {
    n=GWEN_XMLNode_FindNode(currDF, GWEN_XMLNodeTypeTag, "files");
    if (n) {
      n=GWEN_XMLNode_FindFirstTag(n, type, "name", fname);
      if (n) {
        if (isSameLevel) {
          return n;
        }
        if (atoi(GWEN_XMLNode_GetProperty(n, "inAnyDF", "0"))!=0) {
          DBG_DEBUG(LC_LOGDOMAIN, "Returning file from level above");
          return n;
        }
      }
    }
    currDF=GWEN_XMLNode_GetParent(currDF);
    isSameLevel=0;
  }
  DBG_DEBUG(LC_LOGDOMAIN, "%s \"%s\" not found", type, fname);
  return 0;
}
