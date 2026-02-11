mlx5_ib_query_srq(struct ib_srq *ibsrq, struct ib_srq_attr *srq_attr)
{
	struct mlx5_ib_dev *dev = to_mdev(ibsrq->device);
	struct mlx5_ib_srq *srq = to_msrq(ibsrq);
	int ret;
	struct mlx5_query_srq_mbox_out *out;

	out = kzalloc(sizeof(*out), GFP_KERNEL);
	if (!out)
		return -ENOMEM;

	ret = mlx5_core_query_srq(dev->mdev, &srq->msrq, out);
	if (ret)
		goto out_box;

	srq_attr->srq_limit = be16_to_cpu(out->ctx.lwm);
	srq_attr->max_wr    = srq->msrq.max - 1;
	srq_attr->max_sge   = srq->msrq.max_gs;

out_box:
	kfree(out);
	return ret;
}
