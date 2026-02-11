write(struct tty_struct *tty,
		 const unsigned char *buf, int count)
{
	int	c, ret = 0;
	SLMP_INFO *info = tty->driver_data;
	unsigned long flags;

	if (debug_level >= DEBUG_LEVEL_INFO)
		printk("%s(%d):%s write() count=%d\n",
		       __FILE__,__LINE__,info->device_name,count);

	if (sanity_check(info, tty->name, "write"))
		goto cleanup;

	if (!info->tx_buf)
		goto cleanup;

	if (info->params.mode == MGSL_MODE_HDLC) {
		if (count > info->max_frame_size) {
			ret = -EIO;
			goto cleanup;
		}
		if (info->tx_active)
			goto cleanup;
		if (info->tx_count) {


			tx_load_dma_buffer(info, info->tx_buf, info->tx_count);
			goto start;
		}
		ret = info->tx_count = count;
		tx_load_dma_buffer(info, buf, count);
		goto start;
	}

	for (;;) {
		c = min_t(int, count,
			min(info->max_frame_size - info->tx_count - 1,
			    info->max_frame_size - info->tx_put));
		if (c <= 0)
			break;

		memcpy(info->tx_buf + info->tx_put, buf, c);

		spin_lock_irqsave(&info->lock,flags);
		info->tx_put += c;
		if (info->tx_put >= info->max_frame_size)
			info->tx_put -= info->max_frame_size;
		info->tx_count += c;
		spin_unlock_irqrestore(&info->lock,flags);

		buf += c;
		count -= c;
		ret += c;
	}

	if (info->params.mode == MGSL_MODE_HDLC) {
		if (count) {
			ret = info->tx_count = 0;
			goto cleanup;
		}
		tx_load_dma_buffer(info, info->tx_buf, info->tx_count);
	}
start:
 	if (info->tx_count && !tty->stopped && !tty->hw_stopped) {
		spin_lock_irqsave(&info->lock,flags);
		if (!info->tx_active)
		 	tx_start(info);
		spin_unlock_irqrestore(&info->lock,flags);
 	}

cleanup:
	if (debug_level >= DEBUG_LEVEL_INFO)
		printk( "%s(%d):%s write() returning=%d\n",
			__FILE__,__LINE__,info->device_name,ret);
	return ret;
}
