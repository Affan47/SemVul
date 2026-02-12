static int i40e_correct_mac_vlan_filters(struct i40e_vsi *vsi,
					 struct hlist_head *tmp_add_list,
					 struct hlist_head *tmp_del_list,
					 int vlan_filters)
{
	s16 pvid = le16_to_cpu(vsi->info.pvid);
	struct i40e_mac_filter *f, *add_head;
	struct i40e_new_mac_filter *new;
	struct hlist_node *h;
	int bkt, new_vlan;


	hlist_for_each_entry(new, tmp_add_list, hlist) {
		if (pvid && new->f->vlan != pvid)
			new->f->vlan = pvid;
		else if (vlan_filters && new->f->vlan == I40E_VLAN_ANY)
			new->f->vlan = 0;
		else if (!vlan_filters && new->f->vlan == 0)
			new->f->vlan = I40E_VLAN_ANY;
	}


	hash_for_each_safe(vsi->mac_filter_hash, bkt, h, f, hlist) {


		if ((pvid && f->vlan != pvid) ||
		    (vlan_filters && f->vlan == I40E_VLAN_ANY) ||
		    (!vlan_filters && f->vlan == 0)) {

			if (pvid)
				new_vlan = pvid;
			else if (vlan_filters)
				new_vlan = 0;
			else
				new_vlan = I40E_VLAN_ANY;


			add_head = i40e_add_filter(vsi, f->macaddr, new_vlan);
			if (!add_head)
				return -ENOMEM;


			new = kzalloc(sizeof(*new), GFP_ATOMIC);
			if (!new)
				return -ENOMEM;

			new->f = add_head;
			new->state = add_head->state;


			hlist_add_head(&new->hlist, tmp_add_list);


			f->state = I40E_FILTER_REMOVE;
			hash_del(&f->hlist);
			hlist_add_head(&f->hlist, tmp_del_list);
		}
	}

	vsi->has_vlan_filter = !!vlan_filters;

	return 0;
}
