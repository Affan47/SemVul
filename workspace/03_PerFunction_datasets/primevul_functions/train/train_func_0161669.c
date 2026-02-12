static void bond_loadbalance_arp_mon(struct bonding *bond)
{
	struct slave *slave, *oldcurrent;
	struct list_head *iter;
	int do_failover = 0, slave_state_changed = 0;

	if (!bond_has_slaves(bond))
		goto re_arm;

	rcu_read_lock();

	oldcurrent = rcu_dereference(bond->curr_active_slave);


	bond_for_each_slave_rcu(bond, slave, iter) {
		unsigned long trans_start = dev_trans_start(slave->dev);

		bond_propose_link_state(slave, BOND_LINK_NOCHANGE);

		if (slave->link != BOND_LINK_UP) {
			if (bond_time_in_interval(bond, trans_start, 1) &&
			    bond_time_in_interval(bond, slave->last_rx, 1)) {

				bond_propose_link_state(slave, BOND_LINK_UP);
				slave_state_changed = 1;


				if (!oldcurrent) {
					slave_info(bond->dev, slave->dev, "link status definitely up\n");
					do_failover = 1;
				} else {
					slave_info(bond->dev, slave->dev, "interface is now up\n");
				}
			}
		} else {


			if (!bond_time_in_interval(bond, trans_start, 2) ||
			    !bond_time_in_interval(bond, slave->last_rx, 2)) {

				bond_propose_link_state(slave, BOND_LINK_DOWN);
				slave_state_changed = 1;

				if (slave->link_failure_count < UINT_MAX)
					slave->link_failure_count++;

				slave_info(bond->dev, slave->dev, "interface is now down\n");

				if (slave == oldcurrent)
					do_failover = 1;
			}
		}


		if (bond_slave_is_up(slave))
			bond_arp_send_all(bond, slave);
	}

	rcu_read_unlock();

	if (do_failover || slave_state_changed) {
		if (!rtnl_trylock())
			goto re_arm;

		bond_for_each_slave(bond, slave, iter) {
			if (slave->link_new_state != BOND_LINK_NOCHANGE)
				slave->link = slave->link_new_state;
		}

		if (slave_state_changed) {
			bond_slave_state_change(bond);
			if (BOND_MODE(bond) == BOND_MODE_XOR)
				bond_update_slave_arr(bond, NULL);
		}
		if (do_failover) {
			block_netpoll_tx();
			bond_select_active_slave(bond);
			unblock_netpoll_tx();
		}
		rtnl_unlock();
	}

re_arm:
	if (bond->params.arp_interval)
		queue_delayed_work(bond->wq, &bond->arp_work,
				   msecs_to_jiffies(bond->params.arp_interval));
}
