procdraft(const char *filename){
  ESTDOC *doc;
  CBMAP *kwords;
  struct stat sbuf;
  const char *kbuf;
  char *buf, *tbuf, *draft;
  int size, ksiz;
  if(!(buf = cbreadfile(filename, &size))){
    printferror("%s: could not open", filename ? filename : "(stdin)");
    return 1;
  }
  switch(g_filefmt){
  case FF_TEXT:
    doc = est_doc_new_from_text(buf, size, g_inputcode, g_inputlang, g_bincheck);
    break;
  case FF_HTML:
    doc = est_doc_new_from_html(buf, size, g_inputcode, g_inputlang, g_bincheck);
    break;
  case FF_MIME:
    doc = est_doc_new_from_mime(buf, size, g_inputcode, g_inputlang, g_bincheck);
    break;
  default:
    doc = est_doc_new_from_draft_enc(buf, size, g_inputcode);
    break;
  }
  if(!doc){
    printferror("%s: extraction failed", filename ? filename : "(stdin)");
    free(buf);
    return 1;
  }
  if(g_limittsiz >= 0) est_doc_slim(doc, g_limittsiz);
  if(filename && stat(filename, &sbuf) == 0){
    if(!est_doc_attr(doc, ESTDATTRURI)) est_doc_add_attr(doc, ESTDATTRURI, pathtourl(filename));
    if(!est_doc_attr(doc, ESTDATTRMDATE)){
      tbuf = cbdatestrwww(sbuf.st_mtime, 0);
      est_doc_add_attr(doc, ESTDATTRMDATE, tbuf);
      free(tbuf);
    }
  }
  if(g_kwordnum > 0){
    kwords = g_usemorph ? est_morph_etch_doc(doc, g_kwordnum) :
      est_db_etch_doc(NULL, doc, g_kwordnum);
    cbmapiterinit(kwords);
    while((kbuf = cbmapiternext(kwords, &ksiz)) != NULL){
      printf("%s\t%s\n", kbuf, cbmapget(kwords, kbuf, ksiz, NULL));
    }
    cbmapclose(kwords);
  } else {
    draft = est_doc_dump_draft(doc);
    printf("%s", draft);
    free(draft);
  }
  est_doc_delete(doc);
  free(buf);
  return 0;
}
