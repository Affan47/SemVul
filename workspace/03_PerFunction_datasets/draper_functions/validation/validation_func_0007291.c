mthca_free_srq(struct mthca_dev *dev, struct mthca_srq *srq)
{
	struct mthca_mailbox *mailbox;
	int err;

	mailbox = mthca_alloc_mailbox(dev, GFP_KERNEL);
	if (IS_ERR(mailbox)) {
		mthca_warn(dev, "No memory for mailbox to free SRQ.\n");
		return;
	}

	err = mthca_HW2SW_SRQ(dev, mailbox, srq->srqn);
	if (err)
		mthca_warn(dev, "HW2SW_SRQ failed (%d)\n", err);

	spin_lock_irq(&dev->srq_table.lock);
	mthca_array_clear(&dev->srq_table.srq,
			  srq->srqn & (dev->limits.num_srqs - 1));
	--srq->refcount;
	spin_unlock_irq(&dev->srq_table.lock);

	wait_event(srq->wait, !get_srq_refcount(dev, srq));

	if (!srq->ibsrq.uobject) {
		mthca_free_srq_buf(dev, srq);
		if (mthca_is_memfree(dev))
			mthca_free_db(dev, MTHCA_DB_TYPE_SRQ, srq->db_index);
	}

	mthca_table_put(dev, dev->srq_table.table, srq->srqn);
	mthca_free(&dev->srq_table.alloc, srq->srqn);
	mthca_free_mailbox(dev, mailbox);
}
