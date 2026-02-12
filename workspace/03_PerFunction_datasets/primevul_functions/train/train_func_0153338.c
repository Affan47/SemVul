static ssize_t fsl_hv_read(struct file *filp, char __user *buf, size_t len,
			   loff_t *off)
{
	struct doorbell_queue *dbq = filp->private_data;
	uint32_t __user *p = (uint32_t __user *) buf;
	unsigned long flags;
	ssize_t count = 0;


	while (len >= sizeof(uint32_t)) {
		uint32_t dbell;

		spin_lock_irqsave(&dbq->lock, flags);


		if (dbq->head == dbq->tail) {
			spin_unlock_irqrestore(&dbq->lock, flags);
			if (count)
				break;
			if (filp->f_flags & O_NONBLOCK)
				return -EAGAIN;
			if (wait_event_interruptible(dbq->wait,
						     dbq->head != dbq->tail))
				return -ERESTARTSYS;
			continue;
		}


		smp_rmb();


		dbell = dbq->q[dbq->head];
		dbq->head = nextp(dbq->head);

		spin_unlock_irqrestore(&dbq->lock, flags);

		if (put_user(dbell, p))
			return -EFAULT;
		p++;
		count += sizeof(uint32_t);
		len -= sizeof(uint32_t);
	}

	return count;
}
