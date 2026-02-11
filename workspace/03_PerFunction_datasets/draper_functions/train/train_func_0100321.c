be_isr_mcc(int irq, void *dev_id)
{
	struct beiscsi_hba *phba;
	struct be_eq_entry *eqe = NULL;
	struct be_queue_info *eq;
	struct be_queue_info *mcc;
	unsigned int num_eq_processed;
	struct be_eq_obj *pbe_eq;
	unsigned long flags;

	pbe_eq = dev_id;
	eq = &pbe_eq->q;
	phba =  pbe_eq->phba;
	mcc = &phba->ctrl.mcc_obj.cq;
	eqe = queue_tail_node(eq);

	num_eq_processed = 0;

	while (eqe->dw[offsetof(struct amap_eq_entry, valid) / 32]
				& EQE_VALID_MASK) {
		if (((eqe->dw[offsetof(struct amap_eq_entry,
		     resource_id) / 32] &
		     EQE_RESID_MASK) >> 16) == mcc->id) {
			spin_lock_irqsave(&phba->isr_lock, flags);
			pbe_eq->todo_mcc_cq = true;
			spin_unlock_irqrestore(&phba->isr_lock, flags);
		}
		AMAP_SET_BITS(struct amap_eq_entry, valid, eqe, 0);
		queue_tail_inc(eq);
		eqe = queue_tail_node(eq);
		num_eq_processed++;
	}
	if (pbe_eq->todo_mcc_cq)
		queue_work(phba->wq, &pbe_eq->work_cqs);
	if (num_eq_processed)
		hwi_ring_eq_db(phba, eq->id, 1,	num_eq_processed, 1, 1);

	return IRQ_HANDLED;
}
