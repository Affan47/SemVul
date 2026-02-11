bond_slave_changelink(struct net_device *bond_dev,
				 struct net_device *slave_dev,
				 struct nlattr *tb[], struct nlattr *data[])
{
	struct bonding *bond = netdev_priv(bond_dev);
	struct bond_opt_value newval;
	int err;

	if (!data)
		return 0;

	if (data[IFLA_BOND_SLAVE_QUEUE_ID]) {
		u16 queue_id = nla_get_u16(data[IFLA_BOND_SLAVE_QUEUE_ID]);
		char queue_id_str[IFNAMSIZ + 7];


		snprintf(queue_id_str, sizeof(queue_id_str), "%s:%u\n",
			 slave_dev->name, queue_id);
		bond_opt_initstr(&newval, queue_id_str);
		err = __bond_opt_set(bond, BOND_OPT_QUEUE_ID, &newval);
		if (err)
			return err;
	}

	return 0;
}
