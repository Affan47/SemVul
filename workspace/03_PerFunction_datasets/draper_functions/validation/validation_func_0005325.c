ivtv_dma_dec_start(struct ivtv_stream *s)
{
	struct ivtv *itv = s->itv;

	if (s->q_predma.bytesused)
		ivtv_queue_move(s, &s->q_predma, NULL, &s->q_dma, s->q_predma.bytesused);
	s->dma_xfer_cnt++;
	memcpy(s->sg_processing, s->sg_pending, sizeof(struct ivtv_sg_host_element) * s->sg_pending_size);
	s->sg_processing_size = s->sg_pending_size;
	s->sg_pending_size = 0;
	s->sg_processed = 0;

	IVTV_DEBUG_HI_DMA("start DMA for %s\n", s->name);
	itv->dma_retries = 0;
	ivtv_dma_dec_start_xfer(s);
	set_bit(IVTV_F_I_DMA, &itv->i_flags);
	itv->cur_dma_stream = s->type;
}
