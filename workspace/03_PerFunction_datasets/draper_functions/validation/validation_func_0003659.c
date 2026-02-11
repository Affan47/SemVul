dlist_filter(dlist *head, void* aux, lMapFunc func, BOOLEAN deep){
	dlist *run, *nhead = NULL;
	DLIST_ITERATE(run, head){
		if(func(run->data, aux, run)){
			nhead = dlist_pushback(nhead, run->data, deep);
		}
	}
	return nhead;
}
