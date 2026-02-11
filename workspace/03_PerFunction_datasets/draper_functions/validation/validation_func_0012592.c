ioat_start_null_desc(struct ioatdma_chan *ioat_chan)
{
	spin_lock_bh(&ioat_chan->prep_lock);
	if (!test_bit(IOAT_CHAN_DOWN, &ioat_chan->state))
		__ioat_start_null_desc(ioat_chan);
	spin_unlock_bh(&ioat_chan->prep_lock);
}
