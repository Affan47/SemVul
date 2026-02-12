static struct slave *bond_get_slave_by_id(struct bonding *bond,
					  int slave_id)
{
	struct list_head *iter;
	struct slave *slave;
	int i = slave_id;


	bond_for_each_slave_rcu(bond, slave, iter) {
		if (--i < 0) {
			if (bond_slave_can_tx(slave))
				return slave;
		}
	}


	i = slave_id;
	bond_for_each_slave_rcu(bond, slave, iter) {
		if (--i < 0)
			break;
		if (bond_slave_can_tx(slave))
			return slave;
	}

	return NULL;
}
