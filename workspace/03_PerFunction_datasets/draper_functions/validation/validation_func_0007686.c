ivtv_udma_prepare(struct ivtv *itv)
{
	unsigned long flags;

	spin_lock_irqsave(&itv->dma_reg_lock, flags);
	if (!test_bit(IVTV_F_I_DMA, &itv->i_flags))
		ivtv_udma_start(itv);
	else
		set_bit(IVTV_F_I_UDMA_PENDING, &itv->i_flags);
	spin_unlock_irqrestore(&itv->dma_reg_lock, flags);
}
