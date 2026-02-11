mlx5_core_destroy_sq(struct mlx5_core_dev *dev, u32 sqn)
{
	u32 in[MLX5_ST_SZ_DW(destroy_sq_in)];
	u32 out[MLX5_ST_SZ_DW(destroy_sq_out)];

	memset(in, 0, sizeof(in));

	MLX5_SET(destroy_sq_in, in, opcode, MLX5_CMD_OP_DESTROY_SQ);
	MLX5_SET(destroy_sq_in, in, sqn, sqn);

	mlx5_cmd_exec_check_status(dev, in, sizeof(in), out, sizeof(out));
}
