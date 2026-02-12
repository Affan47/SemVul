int edns_opt_list_remove(struct edns_option** list, uint16_t code)
{


	struct edns_option* prev;
	struct edns_option* curr;
	if(!list || !(*list)) return 0;


	while(list && *list && (*list)->opt_code == code) {
		*list = (*list)->next;
	}

	if(!list || !(*list)) return 1;

	prev = *list;
	curr = (*list)->next;
	while(curr != NULL) {
		if(curr->opt_code == code) {
			prev->next = curr->next;
			curr = curr->next;
		} else {
			prev = curr;
			curr = curr->next;
		}
	}
	return 1;
}
