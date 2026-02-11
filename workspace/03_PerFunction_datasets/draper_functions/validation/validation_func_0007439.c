est_doc_set_score(ESTDOC *doc, int score){
  char numbuf[ESTNUMBUFSIZ];
  assert(doc);
  if(!doc->attrs) doc->attrs = cbmapopenex(ESTMINIBNUM);
  if(score >= 0){
    sprintf(numbuf, "%d", score);
    cbmapput(doc->attrs, "\t", 1, numbuf, -1, TRUE);
  } else {
    cbmapout(doc->attrs, "\t", 1);
  }
}
