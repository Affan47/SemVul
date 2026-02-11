rlb_choose_channel(struct sk_buff *skb, struct bonding *bond)
{
	struct alb_bond_info *bond_info = &(BOND_ALB_INFO(bond));
	struct arp_pkt *arp = arp_pkt(skb);
	struct slave *assigned_slave, *curr_active_slave;
	struct rlb_client_info *client_info;
	u32 hash_index = 0;

	spin_lock(&bond->mode_lock);

	curr_active_slave = rcu_dereference(bond->curr_active_slave);

	hash_index = _simple_hash((u8 *)&arp->ip_dst, sizeof(arp->ip_dst));
	client_info = &(bond_info->rx_hashtbl[hash_index]);

	if (client_info->assigned) {
		if ((client_info->ip_src == arp->ip_src) &&
		    (client_info->ip_dst == arp->ip_dst)) {

			if (!ether_addr_equal_64bits(arp->mac_dst, mac_bcast)) {

				ether_addr_copy(client_info->mac_dst, arp->mac_dst);
			}
			ether_addr_copy(client_info->mac_src, arp->mac_src);

			assigned_slave = client_info->slave;
			if (assigned_slave) {
				spin_unlock(&bond->mode_lock);
				return assigned_slave;
			}
		} else {


			if (curr_active_slave &&
			    client_info->slave != curr_active_slave) {
				client_info->slave = curr_active_slave;
				rlb_update_client(client_info);
			}
		}
	}

	assigned_slave = __rlb_next_rx_slave(bond);

	if (assigned_slave) {
		if (!(client_info->assigned &&
		      client_info->ip_src == arp->ip_src)) {


			u32 hash_src = _simple_hash((u8 *)&arp->ip_src,
						    sizeof(arp->ip_src));
			rlb_src_unlink(bond, hash_index);
			rlb_src_link(bond, hash_src, hash_index);
		}

		client_info->ip_src = arp->ip_src;
		client_info->ip_dst = arp->ip_dst;


		ether_addr_copy(client_info->mac_dst, arp->mac_dst);
		ether_addr_copy(client_info->mac_src, arp->mac_src);
		client_info->slave = assigned_slave;

		if (!ether_addr_equal_64bits(client_info->mac_dst, mac_bcast)) {
			client_info->ntt = 1;
			bond->alb_info.rx_ntt = 1;
		} else {
			client_info->ntt = 0;
		}

		if (vlan_get_tag(skb, &client_info->vlan_id))
			client_info->vlan_id = 0;

		if (!client_info->assigned) {
			u32 prev_tbl_head = bond_info->rx_hashtbl_used_head;
			bond_info->rx_hashtbl_used_head = hash_index;
			client_info->used_next = prev_tbl_head;
			if (prev_tbl_head != RLB_NULL_INDEX) {
				bond_info->rx_hashtbl[prev_tbl_head].used_prev =
					hash_index;
			}
			client_info->assigned = 1;
		}
	}

	spin_unlock(&bond->mode_lock);

	return assigned_slave;
}
