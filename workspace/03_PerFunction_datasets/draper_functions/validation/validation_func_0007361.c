sortvector(Vector *v) {
	assert(v->vector[v->count] == NULL);
	qsort(v->vector, v->count, sizeof (char *), qstrcmp);
}
