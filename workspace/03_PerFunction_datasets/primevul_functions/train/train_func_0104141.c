struct edns_option* edns_opt_copy_region(struct edns_option* list,
        struct regional* region)
{
	struct edns_option* result = NULL, *cur = NULL, *s;
	while(list) {

		s = regional_alloc_init(region, list, sizeof(*list));
		if(!s) return NULL;
		s->next = NULL;


		if(s->opt_data) {
			s->opt_data = regional_alloc_init(region, s->opt_data,
				s->opt_len);
			if(!s->opt_data)
				return NULL;
		}


		if(cur)
			cur->next = s;
		else	result = s;
		cur = s;


		list = list->next;
	}
	return result;
}
