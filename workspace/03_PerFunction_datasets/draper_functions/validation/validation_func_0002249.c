mlxsw_sp_port_uc_flood_set(struct mlxsw_sp_port *mlxsw_sp_port,
				      bool set)
{
	struct net_device *dev = mlxsw_sp_port->dev;
	u16 vid, last_visited_vid;
	int err;

	for_each_set_bit(vid, mlxsw_sp_port->active_vlans, VLAN_N_VID) {
		err = __mlxsw_sp_port_flood_set(mlxsw_sp_port, vid, vid, set,
						true);
		if (err) {
			last_visited_vid = vid;
			goto err_port_flood_set;
		}
	}

	return 0;

err_port_flood_set:
	for_each_set_bit(vid, mlxsw_sp_port->active_vlans, last_visited_vid)
		__mlxsw_sp_port_flood_set(mlxsw_sp_port, vid, vid, !set, true);
	netdev_err(dev, "Failed to configure unicast flooding\n");
	return err;
}
