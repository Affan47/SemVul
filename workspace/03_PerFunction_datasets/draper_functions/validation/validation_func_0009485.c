bnad_debugfs_write_regwr(struct file *file, const char __user *buf,
		size_t nbytes, loff_t *ppos)
{
	struct bnad_debug_info *debug = file->private_data;
	struct bnad *bnad = (struct bnad *)debug->i_private;
	struct bfa_ioc *ioc = &bnad->bna.ioceth.ioc;
	int addr, val, rc;
	void __iomem *reg_addr;
	unsigned long flags;
	void *kern_buf;


	kern_buf = memdup_user(buf, nbytes);
	if (IS_ERR(kern_buf))
		return PTR_ERR(kern_buf);

	rc = sscanf(kern_buf, "%x:%x", &addr, &val);
	if (rc < 2) {
		netdev_warn(bnad->netdev, "failed to read user buffer\n");
		kfree(kern_buf);
		return -EINVAL;
	}
	kfree(kern_buf);

	addr &= BFA_REG_ADDRMSK(ioc);


	rc = bna_reg_offset_check(ioc, addr, 1);
	if (rc) {
		netdev_warn(bnad->netdev, "failed reg offset check\n");
		return -EINVAL;
	}

	reg_addr = (bfa_ioc_bar0(ioc)) + addr;
	spin_lock_irqsave(&bnad->bna_lock, flags);
	writel(val, reg_addr);
	spin_unlock_irqrestore(&bnad->bna_lock, flags);

	return nbytes;
}
