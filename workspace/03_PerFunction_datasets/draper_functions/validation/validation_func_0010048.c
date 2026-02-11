vector_add_fast(Vector *sp, Vector *ns, Vector *ret) {
  VectorIterator vit;
  unsigned int col;

  if (!sp || !ns || !ret) {
    if (MATR_DEBUG_MODE) {
      fprintf(stderr, "vector_add: null arguments.\n");
    }
    return;
  }

  if (ret != ns || sp->type == NON_SPARSE || ns->type != NON_SPARSE) {
    if (MATR_DEBUG_MODE) {
      fprintf(stderr, "vector_add_fast: Wrong sparseness.\n");
    }
    vector_add(sp, ns, ret);
    return;
  }

  vectorit_set_at_beg(&vit, sp);
  while (!vectorit_past_end(vit, sp)) {
    col = vectorit_curr_col(vit, sp);
    vector_set(ret, col, vectorit_curr_val(vit, sp) + vector_get(ns, col));
    vectorit_next(&vit, sp);
  }
}
