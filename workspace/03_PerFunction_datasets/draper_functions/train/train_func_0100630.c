reclaim_pages(struct mlx5_core_dev *dev, u32 func_id, int npages,
			 int *nclaimed)
{
	struct mlx5_manage_pages_inbox   in;
	struct mlx5_manage_pages_outbox *out;
	int num_claimed;
	int outlen;
	u64 addr;
	int err;
	int i;

	if (nclaimed)
		*nclaimed = 0;

	memset(&in, 0, sizeof(in));
	outlen = sizeof(*out) + npages * sizeof(out->pas[0]);
	out = mlx5_vzalloc(outlen);
	if (!out)
		return -ENOMEM;

	in.hdr.opcode = cpu_to_be16(MLX5_CMD_OP_MANAGE_PAGES);
	in.hdr.opmod = cpu_to_be16(MLX5_PAGES_TAKE);
	in.func_id = cpu_to_be16(func_id);
	in.num_entries = cpu_to_be32(npages);
	mlx5_core_dbg(dev, "npages %d, outlen %d\n", npages, outlen);
	err = mlx5_cmd_exec(dev, &in, sizeof(in), out, outlen);
	if (err) {
		mlx5_core_err(dev, "failed reclaiming pages\n");
		goto out_free;
	}
	dev->priv.fw_pages -= npages;

	if (out->hdr.status) {
		err = mlx5_cmd_status_to_err(&out->hdr);
		goto out_free;
	}

	num_claimed = be32_to_cpu(out->num_entries);
	if (num_claimed > npages) {
		mlx5_core_warn(dev, "fw returned %d, driver asked %d => corruption\n",
			       num_claimed, npages);
		err = -EINVAL;
		goto out_free;
	}
	if (nclaimed)
		*nclaimed = num_claimed;

	for (i = 0; i < num_claimed; i++) {
		addr = be64_to_cpu(out->pas[i]);
		free_4k(dev, addr);
	}
	dev->priv.fw_pages -= num_claimed;
	if (func_id)
		dev->priv.vfs_pages -= num_claimed;

out_free:
	kvfree(out);
	return err;
}
