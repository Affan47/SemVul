mcam_cleanup_vb2(struct mcam_camera *cam)
{
#ifdef MCAM_MODE_DMA_CONTIG
	if (cam->buffer_mode == B_DMA_contig)
		vb2_dma_contig_cleanup_ctx(cam->vb_alloc_ctx);
#endif
#ifdef MCAM_MODE_DMA_SG
	if (cam->buffer_mode == B_DMA_sg)
		vb2_dma_sg_cleanup_ctx(cam->vb_alloc_ctx_sg);
#endif
}
