g2_packet_leaf_qht_match(g2_connection_t *con, void *data)
{
	struct ptype_action_args *parg = data;
	g2_packet_t *t, *source = parg->source;

	t = g2_packet_clone(source);
	if(!t)
		return 0;


	if(source->data_trunk_is_freeable) {
		struct packet_data_store *pds =
			container_of(source->data_trunk.data,
			             struct packet_data_store, data);
		atomic_inc(&pds->refcnt);
	} else {

		if(source->data_trunk.data >= source->pd.out &&
		   source->data_trunk.data < &source->pd.out[sizeof(source->pd.out)]) {
			ptrdiff_t diff = source->data_trunk.data - source->pd.out;
			t->data_trunk.data = &t->pd.out[diff];
		}
		else
		{


			if(!g2_packet_steal_data_space_lit(t, buffer_remaining(source->data_trunk))) {
				g2_packet_free(t);
				return 0;
			}
			my_memcpy(buffer_start(t->data_trunk), buffer_start(source->data_trunk),
			          buffer_remaining(source->data_trunk));
		}
	}
	t->is_literal = true;


	g2_handler_con_mark_write(t, con);
	return 0;
}
