mlxsw_sp_port_fdb_static_add(struct mlxsw_sp_port *mlxsw_sp_port,
			     const struct switchdev_obj_port_fdb *fdb,
			     struct switchdev_trans *trans)
{
	if (switchdev_trans_ph_prepare(trans))
		return 0;

	return mlxsw_sp_port_fdb_op(mlxsw_sp_port, fdb->addr, fdb->vid,
				    true, false);
}
