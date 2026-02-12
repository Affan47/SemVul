static void kvm_clock_sync_scb(struct kvm_s390_sie_block *scb, u64 delta)
{
	u8 delta_idx = 0;


	delta = -delta;


	if ((s64)delta < 0)
		delta_idx = -1;

	scb->epoch += delta;
	if (scb->ecd & ECD_MEF) {
		scb->epdx += delta_idx;
		if (scb->epoch < delta)
			scb->epdx += 1;
	}
}
