linked_option_space_encapsulate (result, packet, lease, client_state,
				    in_options, cfg_options, scope, universe)
	struct data_string *result;
	struct packet *packet;
	struct lease *lease;
	struct client_state *client_state;
	struct option_state *in_options;
	struct option_state *cfg_options;
	struct binding_scope **scope;
	struct universe *universe;
{
	int status = 0;
	pair oc;
	struct option_chain_head *head;

	if (universe -> index >= cfg_options -> universe_count)
		return status;
	head = ((struct option_chain_head *)
		cfg_options -> universes [universe -> index]);
	if (!head)
		return status;

	for (oc = head -> first; oc; oc = oc -> cdr) {
		if (store_option (result, universe, packet,
				  lease, client_state, in_options, cfg_options,
				  scope, (struct option_cache *)(oc -> car)))
			status = 1;
	}

	if (search_subencapsulation(result, packet, lease, client_state,
				    in_options, cfg_options, scope, universe))
		status = 1;

	return status;
}
