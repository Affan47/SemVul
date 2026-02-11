s5p_mfc_run_init_dec(struct s5p_mfc_ctx *ctx)
{
	struct s5p_mfc_dev *dev = ctx->dev;
	unsigned long flags;
	struct s5p_mfc_buf *temp_vb;


	spin_lock_irqsave(&dev->irqlock, flags);
	mfc_debug(2, "Preparing to init decoding\n");
	temp_vb = list_entry(ctx->src_queue.next, struct s5p_mfc_buf, list);
	s5p_mfc_set_dec_desc_buffer(ctx);
	mfc_debug(2, "Header size: %d\n",
			temp_vb->b->vb2_buf.planes[0].bytesused);
	s5p_mfc_set_dec_stream_buffer_v5(ctx,
			vb2_dma_contig_plane_dma_addr(&temp_vb->b->vb2_buf, 0),
			0, temp_vb->b->vb2_buf.planes[0].bytesused);
	spin_unlock_irqrestore(&dev->irqlock, flags);
	dev->curr_ctx = ctx->num;
	s5p_mfc_init_decode_v5(ctx);
}
