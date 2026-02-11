query_rmp_cmd(struct mlx5_core_dev *dev, struct mlx5_core_srq *srq,
			 struct mlx5_query_srq_mbox_out *out)
{
	u32 *rmp_out;
	void *rmpc;
	void *srqc;
	int err;

	rmp_out =  mlx5_vzalloc(MLX5_ST_SZ_BYTES(query_rmp_out));
	if (!rmp_out)
		return -ENOMEM;

	err = mlx5_core_query_rmp(dev, srq->srqn, rmp_out);
	if (err)
		goto out;

	srqc = MLX5_ADDR_OF(query_srq_out, out,	    srq_context_entry);
	rmpc = MLX5_ADDR_OF(query_rmp_out, rmp_out, rmp_context);
	rmpc_srqc_reformat(srqc, rmpc, false);

out:
	kvfree(rmp_out);
	return err;
}
