list_sort( List *l, int (*compare)(const void *, const void *) ) {
  Element *temp, *prev;
  int i, sorted;
  progress_counter_t *pc = NULL;

  if ( !l )
    return;


  pc = open_progress(l->n,"list_sort");

  for (i = 0; i < l->n; i++ ) {
    sorted = 1;
    for ( temp = l->start.next->next;
          temp != NULL && temp != &l->stop; temp = temp->next ) {
      if ( temp->previous == &l->start ) continue;
      if ( compare((const void *)temp->previous->data,
                   (const void *)temp->data) > 0 ) {

        sorted = 0;

	prev = temp->previous;
  	prev->previous->next = temp;
        temp->next->previous = prev;
	temp->previous = prev->previous;
	prev->next     = temp->next;
	prev->previous = temp;
	temp->next     = prev;

	temp = prev;

#ifdef SLOWER_BUT_KEEP_BY_NOW

        void *data;

	data = temp->data;
	prev = temp->previous;
	list_del(l, data);
	list_ins(l, prev->data, data);
	temp = prev;
#endif
      }
    }
    if (sorted) break;
    progress(i,pc);
  }

  close_progress(pc);
  g_debug(fprintf(stderr, "LEV3: list_sort()\n");)
}
