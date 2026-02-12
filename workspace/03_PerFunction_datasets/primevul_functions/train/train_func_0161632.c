static int bond_neigh_setup(struct net_device *dev,
			    struct neigh_parms *parms)
{

	if (parms->dev == dev)
		parms->neigh_setup = bond_neigh_init;

	return 0;
}
