bnx2x_get_n_elements(struct bnx2x *bp, struct bnx2x_vlan_mac_obj *o,
				int n, u8 *base, u8 stride, u8 size)
{
	struct bnx2x_vlan_mac_registry_elem *pos;
	u8 *next = base;
	int counter = 0;
	int read_lock;

	DP(BNX2X_MSG_SP, "get_n_elements - taking vlan_mac_lock (reader)\n");
	read_lock = bnx2x_vlan_mac_h_read_lock(bp, o);
	if (read_lock != 0)
		BNX2X_ERR("get_n_elements failed to get vlan mac reader lock; Access without lock\n");


	list_for_each_entry(pos, &o->head, link) {
		if (counter < n) {
			memcpy(next, &pos->u, size);
			counter++;
			DP(BNX2X_MSG_SP, "copied element number %d to address %p element was:\n",
			   counter, next);
			next += stride + size;
		}
	}

	if (read_lock == 0) {
		DP(BNX2X_MSG_SP, "get_n_elements - releasing vlan_mac_lock (reader)\n");
		bnx2x_vlan_mac_h_read_unlock(bp, o);
	}

	return counter * ETH_ALEN;
}
