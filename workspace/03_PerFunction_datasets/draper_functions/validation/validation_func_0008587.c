mlx5_set_port_mtu(struct mlx5_core_dev *dev, u16 mtu, u8 port)
{
	u32 in[MLX5_ST_SZ_DW(pmtu_reg)];
	u32 out[MLX5_ST_SZ_DW(pmtu_reg)];

	memset(in, 0, sizeof(in));

	MLX5_SET(pmtu_reg, in, admin_mtu, mtu);
	MLX5_SET(pmtu_reg, in, local_port, port);

	return mlx5_core_access_reg(dev, in, sizeof(in), out,
				   sizeof(out), MLX5_REG_PMTU, 0, 1);
}
