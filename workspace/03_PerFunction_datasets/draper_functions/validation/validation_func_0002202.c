e100_exec_cmd(struct nic *nic, u8 cmd, dma_addr_t dma_addr)
{
	unsigned long flags;
	unsigned int i;
	int err = 0;

	spin_lock_irqsave(&nic->cmd_lock, flags);


	for (i = 0; i < E100_WAIT_SCB_TIMEOUT; i++) {
		if (likely(!ioread8(&nic->csr->scb.cmd_lo)))
			break;
		cpu_relax();
		if (unlikely(i > E100_WAIT_SCB_FAST))
			udelay(5);
	}
	if (unlikely(i == E100_WAIT_SCB_TIMEOUT)) {
		err = -EAGAIN;
		goto err_unlock;
	}

	if (unlikely(cmd != cuc_resume))
		iowrite32(dma_addr, &nic->csr->scb.gen_ptr);
	iowrite8(cmd, &nic->csr->scb.cmd_lo);

err_unlock:
	spin_unlock_irqrestore(&nic->cmd_lock, flags);

	return err;
}
