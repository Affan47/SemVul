static void listfield (LexState *ls, ConsControl *cc) {

  expr(ls, &cc->v);
  cc->tostore++;
}
