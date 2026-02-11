mlx5_query_port_mtu(struct mlx5_core_dev *dev, u16 *admin_mtu,
				u16 *max_mtu, u16 *oper_mtu, u8 port)
{
	u32 in[MLX5_ST_SZ_DW(pmtu_reg)];
	u32 out[MLX5_ST_SZ_DW(pmtu_reg)];

	memset(in, 0, sizeof(in));

	MLX5_SET(pmtu_reg, in, local_port, port);

	mlx5_core_access_reg(dev, in, sizeof(in), out,
			     sizeof(out), MLX5_REG_PMTU, 0, 0);

	if (max_mtu)
		*max_mtu  = MLX5_GET(pmtu_reg, out, max_mtu);
	if (oper_mtu)
		*oper_mtu = MLX5_GET(pmtu_reg, out, oper_mtu);
	if (admin_mtu)
		*admin_mtu = MLX5_GET(pmtu_reg, out, admin_mtu);
}
