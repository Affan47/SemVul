nativeCallGetCType(JsLex *lex) {
  if (lex->tk == LEX_R_VOID) {
    jslMatch(lex, LEX_R_VOID);
    return JSWAT_VOID;
  }
  if (lex->tk == LEX_ID) {
    int t = -1;
    char *name = jslGetTokenValueAsString(lex);
    if (strcmp(name,"int")==0) t=JSWAT_INT32;
    if (strcmp(name,"double")==0) t=JSWAT_JSVARFLOAT;
    if (strcmp(name,"bool")==0) t=JSWAT_BOOL;
    if (strcmp(name,"Pin")==0) t=JSWAT_PIN;
    if (strcmp(name,"JsVar")==0) t=JSWAT_JSVAR;
    jslMatch(lex, LEX_ID);
    return t;
  }
  return -1;
}
