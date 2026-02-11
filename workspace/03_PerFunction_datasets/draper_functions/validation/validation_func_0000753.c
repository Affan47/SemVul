bstrListCreate (void) {
struct bstrList * sl = (struct bstrList *) bstr__alloc (sizeof (struct bstrList));
	if (sl) {
		sl->entry = (bstring *) bstr__alloc (1*sizeof (bstring));
		if (!sl->entry) {
			bstr__free (sl);
			sl = NULL;
		} else {
			sl->qty = 0;
			sl->mlen = 1;
		}
	}
	return sl;
}
