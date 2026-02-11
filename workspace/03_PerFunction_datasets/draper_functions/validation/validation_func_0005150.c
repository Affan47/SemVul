efx_farch_filter_get_rx_ids(struct efx_nic *efx,
				enum efx_filter_priority priority,
				u32 *buf, u32 size)
{
	struct efx_farch_filter_state *state = efx->filter_state;
	enum efx_farch_filter_table_id table_id;
	struct efx_farch_filter_table *table;
	unsigned int filter_idx;
	s32 count = 0;

	spin_lock_bh(&efx->filter_lock);

	for (table_id = EFX_FARCH_FILTER_TABLE_RX_IP;
	     table_id <= EFX_FARCH_FILTER_TABLE_RX_DEF;
	     table_id++) {
		table = &state->table[table_id];
		for (filter_idx = 0; filter_idx < table->size; filter_idx++) {
			if (test_bit(filter_idx, table->used_bitmap) &&
			    table->spec[filter_idx].priority == priority) {
				if (count == size) {
					count = -EMSGSIZE;
					goto out;
				}
				buf[count++] = efx_farch_filter_make_id(
					&table->spec[filter_idx], filter_idx);
			}
		}
	}
out:
	spin_unlock_bh(&efx->filter_lock);

	return count;
}
