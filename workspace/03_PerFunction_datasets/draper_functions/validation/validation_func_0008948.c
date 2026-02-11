i2400m_rx_stats_write(struct file *filp, const char __user *buffer,
			      size_t count, loff_t *ppos)
{
	struct i2400m *i2400m = filp->private_data;
	unsigned long flags;

	spin_lock_irqsave(&i2400m->rx_lock, flags);
	i2400m->rx_pl_num = 0;
	i2400m->rx_pl_max = 0;
	i2400m->rx_pl_min = UINT_MAX;
	i2400m->rx_num = 0;
	i2400m->rx_size_acc = 0;
	i2400m->rx_size_min = UINT_MAX;
	i2400m->rx_size_max = 0;
	spin_unlock_irqrestore(&i2400m->rx_lock, flags);
	return count;
}
