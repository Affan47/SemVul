mlx5_core_create_mkey(struct mlx5_core_dev *dev, struct mlx5_core_mr *mr,
			  struct mlx5_create_mkey_mbox_in *in, int inlen,
			  mlx5_cmd_cbk_t callback, void *context,
			  struct mlx5_create_mkey_mbox_out *out)
{
	struct mlx5_mr_table *table = &dev->priv.mr_table;
	struct mlx5_create_mkey_mbox_out lout;
	int err;
	u8 key;

	memset(&lout, 0, sizeof(lout));
	spin_lock_irq(&dev->priv.mkey_lock);
	key = dev->priv.mkey_key++;
	spin_unlock_irq(&dev->priv.mkey_lock);
	in->seg.qpn_mkey7_0 |= cpu_to_be32(key);
	in->hdr.opcode = cpu_to_be16(MLX5_CMD_OP_CREATE_MKEY);
	if (callback) {
		err = mlx5_cmd_exec_cb(dev, in, inlen, out, sizeof(*out),
				       callback, context);
		return err;
	} else {
		err = mlx5_cmd_exec(dev, in, inlen, &lout, sizeof(lout));
	}

	if (err) {
		mlx5_core_dbg(dev, "cmd exec failed %d\n", err);
		return err;
	}

	if (lout.hdr.status) {
		mlx5_core_dbg(dev, "status %d\n", lout.hdr.status);
		return mlx5_cmd_status_to_err(&lout.hdr);
	}

	mr->iova = be64_to_cpu(in->seg.start_addr);
	mr->size = be64_to_cpu(in->seg.len);
	mr->key = mlx5_idx_to_mkey(be32_to_cpu(lout.mkey) & 0xffffff) | key;
	mr->pd = be32_to_cpu(in->seg.flags_pd) & 0xffffff;

	mlx5_core_dbg(dev, "out 0x%x, key 0x%x, mkey 0x%x\n",
		      be32_to_cpu(lout.mkey), key, mr->key);


	write_lock_irq(&table->lock);
	err = radix_tree_insert(&table->tree, mlx5_base_mkey(mr->key), mr);
	write_unlock_irq(&table->lock);
	if (err) {
		mlx5_core_warn(dev, "failed radix tree insert of mr 0x%x, %d\n",
			       mlx5_base_mkey(mr->key), err);
		mlx5_core_destroy_mkey(dev, mr);
	}

	return err;
}
