static int bond_neigh_init(struct neighbour *n)
{
	struct bonding *bond = netdev_priv(n->dev);
	const struct net_device_ops *slave_ops;
	struct neigh_parms parms;
	struct slave *slave;
	int ret = 0;

	rcu_read_lock();
	slave = bond_first_slave_rcu(bond);
	if (!slave)
		goto out;
	slave_ops = slave->dev->netdev_ops;
	if (!slave_ops->ndo_neigh_setup)
		goto out;


	memset(&parms, 0, sizeof(parms));
	ret = slave_ops->ndo_neigh_setup(slave->dev, &parms);

	if (ret)
		goto out;

	if (parms.neigh_setup)
		ret = parms.neigh_setup(n);
out:
	rcu_read_unlock();
	return ret;
}
