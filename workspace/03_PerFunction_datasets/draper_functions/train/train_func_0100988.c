stage3list_gc (List_T *old) {
  List_T p;
  Stage3end_T hit;

  for (p = *old; p != NULL; p = p->rest) {
    hit = (Stage3end_T) p->first;
    Stage3end_free(&hit);
  }
  List_free(&(*old));
  return;
}
