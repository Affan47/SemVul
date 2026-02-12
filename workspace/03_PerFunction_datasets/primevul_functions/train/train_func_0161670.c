static int bond_ab_arp_inspect(struct bonding *bond)
{
	unsigned long trans_start, last_rx;
	struct list_head *iter;
	struct slave *slave;
	int commit = 0;

	bond_for_each_slave_rcu(bond, slave, iter) {
		bond_propose_link_state(slave, BOND_LINK_NOCHANGE);
		last_rx = slave_last_rx(bond, slave);

		if (slave->link != BOND_LINK_UP) {
			if (bond_time_in_interval(bond, last_rx, 1)) {
				bond_propose_link_state(slave, BOND_LINK_UP);
				commit++;
			} else if (slave->link == BOND_LINK_BACK) {
				bond_propose_link_state(slave, BOND_LINK_FAIL);
				commit++;
			}
			continue;
		}


		if (bond_time_in_interval(bond, slave->last_link_up, 2))
			continue;


		if (!bond_is_active_slave(slave) &&
		    !rcu_access_pointer(bond->current_arp_slave) &&
		    !bond_time_in_interval(bond, last_rx, 3)) {
			bond_propose_link_state(slave, BOND_LINK_DOWN);
			commit++;
		}


		trans_start = dev_trans_start(slave->dev);
		if (bond_is_active_slave(slave) &&
		    (!bond_time_in_interval(bond, trans_start, 2) ||
		     !bond_time_in_interval(bond, last_rx, 2))) {
			bond_propose_link_state(slave, BOND_LINK_DOWN);
			commit++;
		}
	}

	return commit;
}
