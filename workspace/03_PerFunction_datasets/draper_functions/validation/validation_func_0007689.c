dlist_length(dlist *head){
	if(head == NULL) return 0;
	dlist *run = head;
	size_t i = 0;
	do {
		i++;
		run = run->next;
	} while(run != head);
	return i;
}
