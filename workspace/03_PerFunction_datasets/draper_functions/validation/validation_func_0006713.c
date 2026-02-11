Ntuple_transposable(const iodim *a, const iodim *b, INT vl, INT vs)
{
     return (vs == 1 && b->is == vl && a->os == vl &&
	     ((a->n == b->n && a->is == b->os
	       && a->is >= b->n && a->is % vl == 0)
	      || (a->is == b->n * vl && b->os == a->n * vl)));
}
