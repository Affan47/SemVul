mlx4_set_vf_vlan(struct mlx4_dev *dev, int port, int vf, u16 vlan, u8 qos)
{
	struct mlx4_priv *priv = mlx4_priv(dev);
	struct mlx4_vport_state *vf_admin;
	int slave;

	if ((!mlx4_is_master(dev)) ||
	    !(dev->caps.flags2 & MLX4_DEV_CAP_FLAG2_VLAN_CONTROL))
		return -EPROTONOSUPPORT;

	if ((vlan > 4095) || (qos > 7))
		return -EINVAL;

	slave = mlx4_get_slave_indx(dev, vf);
	if (slave < 0)
		return -EINVAL;

	port = mlx4_slaves_closest_port(dev, slave, port);
	vf_admin = &priv->mfunc.master.vf_admin[slave].vport[port];

	if (!mlx4_valid_vf_state_change(dev, port, vf_admin, vlan, qos))
		return -EPERM;

	if ((0 == vlan) && (0 == qos))
		vf_admin->default_vlan = MLX4_VGT;
	else
		vf_admin->default_vlan = vlan;
	vf_admin->default_qos = qos;


	if (mlx4_is_vf_vst_and_prio_qos(dev, port, vf_admin) &&
	    vf_admin->tx_rate)
		vf_admin->qos_vport = slave;

	if (mlx4_master_immediate_activate_vlan_qos(priv, slave, port))
		mlx4_info(dev,
			  "updating vf %d port %d config will take effect on next VF restart\n",
			  vf, port);
	return 0;
}
