delete_clauses(Plist p)
{
  if (p != NULL) {
    delete_clauses(p->next);
    delete_clause(p->v);
    free_plist(p);
  }
}
