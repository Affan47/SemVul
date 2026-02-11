search_idle_in_networks(struct search_idle_state *s,
	int nnets, struct search_idle_network **nets)
{
	int i;
	struct search_idle_host_state *h;
	gfarm_error_t e;
	int rv;


	for (i = 0; i < nnets; i++) {
		for (h = nets[i]->candidate_list;
		    h != NULL; h = h->next_in_the_net) {
			if (search_idle_cache_is_available(s, h)) {
				search_idle_record_host(s, h);
				h->flags |= HOST_STATE_FLAG_CACHE_WAS_USED;
			}
		}
	}
	if (search_idle_is_satisfied(s))
		return;


	for (i = 0; i < nnets; i++) {
		for (h = nets[i]->candidate_list;
		    h != NULL; h = h->next_in_the_net) {

			e = search_idle_try_host(s, h, 1);
			if (search_idle_is_satisfied(s))
				goto end_of_trial;
		}
	}
end_of_trial:
	rv = gfarm_eventqueue_loop(s->q, NULL);
	if (search_idle_is_satisfied(s))
		return;


	for (i = 0; i < nnets; i++) {
		for (h = nets[i]->candidate_list;
		    h != NULL; h = h->next_in_the_net) {
			if ((h->flags & HOST_STATE_FLAG_CACHE_WAS_USED) != 0)
				search_idle_forget_scheduled(s, h);
		}
	}
}
