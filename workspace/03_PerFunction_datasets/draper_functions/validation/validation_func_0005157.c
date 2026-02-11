tifm_ms_issue_cmd(struct tifm_ms *host)
{
	struct tifm_dev *sock = host->dev;
	unsigned char *data;
	unsigned int data_len, cmd, sys_param;

	host->cmd_flags = 0;
	host->block_pos = 0;
	host->io_pos = 0;
	host->io_word = 0;
	host->cmd_flags = 0;

	data = host->req->data;

	host->use_dma = !no_dma;

	if (host->req->long_data) {
		data_len = host->req->sg.length;
		if (!is_power_of_2(data_len))
			host->use_dma = 0;
	} else {
		data_len = host->req->data_len;
		host->use_dma = 0;
	}

	writel(TIFM_FIFO_INT_SETALL,
	       sock->addr + SOCK_DMA_FIFO_INT_ENABLE_CLEAR);
	writel(TIFM_FIFO_ENABLE,
	       sock->addr + SOCK_FIFO_CONTROL);

	if (host->use_dma) {
		if (1 != tifm_map_sg(sock, &host->req->sg, 1,
				     host->req->data_dir == READ
				     ? PCI_DMA_FROMDEVICE
				     : PCI_DMA_TODEVICE)) {
			host->req->error = -ENOMEM;
			return host->req->error;
		}
		data_len = sg_dma_len(&host->req->sg);

		writel(ilog2(data_len) - 2,
		       sock->addr + SOCK_FIFO_PAGE_SIZE);
		writel(TIFM_FIFO_INTMASK,
		       sock->addr + SOCK_DMA_FIFO_INT_ENABLE_SET);
		sys_param = TIFM_DMA_EN | (1 << 8);
		if (host->req->data_dir == WRITE)
			sys_param |= TIFM_DMA_TX;

		writel(TIFM_FIFO_INTMASK,
		       sock->addr + SOCK_DMA_FIFO_INT_ENABLE_SET);

		writel(sg_dma_address(&host->req->sg),
		       sock->addr + SOCK_DMA_ADDRESS);
		writel(sys_param, sock->addr + SOCK_DMA_CONTROL);
	} else {
		writel(host->mode_mask | TIFM_MS_SYS_FIFO,
		       sock->addr + SOCK_MS_SYSTEM);

		writel(TIFM_FIFO_MORE,
		       sock->addr + SOCK_DMA_FIFO_INT_ENABLE_SET);
	}

	mod_timer(&host->timer, jiffies + host->timeout_jiffies);
	writel(TIFM_CTRL_LED | readl(sock->addr + SOCK_CONTROL),
	       sock->addr + SOCK_CONTROL);
	host->req->error = 0;

	sys_param = readl(sock->addr + SOCK_MS_SYSTEM);
	sys_param |= TIFM_MS_SYS_INTCLR;

	if (host->use_dma)
		sys_param |= TIFM_MS_SYS_DMA;
	else
		sys_param &= ~TIFM_MS_SYS_DMA;

	writel(sys_param, sock->addr + SOCK_MS_SYSTEM);

	cmd = (host->req->tpc & 0xf) << 12;
	cmd |= data_len;
	writel(cmd, sock->addr + SOCK_MS_COMMAND);

	dev_dbg(&sock->dev, "executing TPC %x, %x\n", cmd, sys_param);
	return 0;
}
