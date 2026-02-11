zap_term(struct term *t)
{
  struct rel *r1, *r2;

  if (t->occ.rel != NULL) {
    fprintf(stderr, "WARNING, zap_term, contained term.\n");
    printf("WARNING, zap_term, contained term: ");
    print_term_nl(stdout, t);
    printf("\n");
  }
  else {
    if (t->type == COMPLEX) {
      r1 = t->farg;
      while (r1 != NULL) {
	zap_term(r1->argval);
	r2 = r1;
	r1 = r1->narg;
	free_rel(r2);
      }
    }
    free_term(t);
  }
}
