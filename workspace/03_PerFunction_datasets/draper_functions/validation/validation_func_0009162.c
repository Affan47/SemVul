qlcnic_add_lb_filter(struct qlcnic_adapter *adapter,
				 struct sk_buff *skb, int loopback_pkt, u16 vlan_id)
{
	struct ethhdr *phdr = (struct ethhdr *)(skb->data);
	struct qlcnic_filter *fil, *tmp_fil;
	struct hlist_head *head;
	unsigned long time;
	u64 src_addr = 0;
	u8 hindex, op;
	int ret;

	if (!qlcnic_sriov_pf_check(adapter) || (vlan_id == 0xffff))
		vlan_id = 0;

	memcpy(&src_addr, phdr->h_source, ETH_ALEN);
	hindex = qlcnic_mac_hash(src_addr, vlan_id) &
		 (adapter->fhash.fbucket_size - 1);

	if (loopback_pkt) {
		if (adapter->rx_fhash.fnum >= adapter->rx_fhash.fmax)
			return;

		head = &(adapter->rx_fhash.fhead[hindex]);

		tmp_fil = qlcnic_find_mac_filter(head, &src_addr, vlan_id);
		if (tmp_fil) {
			time = tmp_fil->ftime;
			if (time_after(jiffies, QLCNIC_READD_AGE * HZ + time))
				tmp_fil->ftime = jiffies;
			return;
		}

		fil = kzalloc(sizeof(struct qlcnic_filter), GFP_ATOMIC);
		if (!fil)
			return;

		fil->ftime = jiffies;
		memcpy(fil->faddr, &src_addr, ETH_ALEN);
		fil->vlan_id = vlan_id;
		spin_lock(&adapter->rx_mac_learn_lock);
		hlist_add_head(&(fil->fnode), head);
		adapter->rx_fhash.fnum++;
		spin_unlock(&adapter->rx_mac_learn_lock);
	} else {
		head = &adapter->fhash.fhead[hindex];

		spin_lock(&adapter->mac_learn_lock);

		tmp_fil = qlcnic_find_mac_filter(head, &src_addr, vlan_id);
		if (tmp_fil) {
			op = vlan_id ? QLCNIC_MAC_VLAN_DEL : QLCNIC_MAC_DEL;
			ret = qlcnic_sre_macaddr_change(adapter,
							(u8 *)&src_addr,
							vlan_id, op);
			if (!ret) {
				hlist_del(&tmp_fil->fnode);
				adapter->fhash.fnum--;
			}

			spin_unlock(&adapter->mac_learn_lock);

			return;
		}

		spin_unlock(&adapter->mac_learn_lock);

		head = &adapter->rx_fhash.fhead[hindex];

		spin_lock(&adapter->rx_mac_learn_lock);

		tmp_fil = qlcnic_find_mac_filter(head, &src_addr, vlan_id);
		if (tmp_fil)
			qlcnic_delete_rx_list_mac(adapter, tmp_fil, &src_addr,
						  vlan_id);

		spin_unlock(&adapter->rx_mac_learn_lock);
	}
}
