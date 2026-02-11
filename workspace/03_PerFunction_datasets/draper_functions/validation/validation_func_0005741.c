mlx5e_build_tx_cq_param(struct mlx5e_priv *priv,
				    struct mlx5e_cq_param *param)
{
	void *cqc = param->cqc;

	MLX5_SET(cqc, cqc, log_cq_size,  priv->params.log_sq_size);

	mlx5e_build_common_cq_param(priv, param);
}
