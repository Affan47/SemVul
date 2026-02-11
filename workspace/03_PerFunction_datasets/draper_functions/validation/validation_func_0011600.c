Uinttable_values (T table) {
  void **valuearray;
  int i, j = 0;
  struct binding *p;

  assert(table);
  valuearray = (void **) CALLOC(table->length,sizeof(void *));
  for (i = 0; i < table->size; i++) {
    for (p = table->buckets[i]; p; p = p->link) {
      valuearray[j++] = (void *) p->value;
    }
  }
  return valuearray;
}
