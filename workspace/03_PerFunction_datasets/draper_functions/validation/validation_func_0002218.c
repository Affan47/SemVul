s5p_mfc_buf_init(struct vb2_buffer *vb)
{
	struct vb2_v4l2_buffer *vbuf = to_vb2_v4l2_buffer(vb);
	struct vb2_queue *vq = vb->vb2_queue;
	struct s5p_mfc_ctx *ctx = fh_to_ctx(vq->drv_priv);
	unsigned int i;
	int ret;

	if (vq->type == V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE) {
		ret = check_vb_with_fmt(ctx->dst_fmt, vb);
		if (ret < 0)
			return ret;
		i = vb->index;
		ctx->dst_bufs[i].b = vbuf;
		ctx->dst_bufs[i].cookie.stream =
					vb2_dma_contig_plane_dma_addr(vb, 0);
		ctx->dst_bufs_cnt++;
	} else if (vq->type == V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE) {
		ret = check_vb_with_fmt(ctx->src_fmt, vb);
		if (ret < 0)
			return ret;
		i = vb->index;
		ctx->src_bufs[i].b = vbuf;
		ctx->src_bufs[i].cookie.raw.luma =
					vb2_dma_contig_plane_dma_addr(vb, 0);
		ctx->src_bufs[i].cookie.raw.chroma =
					vb2_dma_contig_plane_dma_addr(vb, 1);
		ctx->src_bufs_cnt++;
	} else {
		mfc_err("invalid queue type: %d\n", vq->type);
		return -EINVAL;
	}
	return 0;
}
