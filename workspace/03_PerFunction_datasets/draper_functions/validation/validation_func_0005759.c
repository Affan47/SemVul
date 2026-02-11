emmaprp_buf_prepare(struct vb2_buffer *vb)
{
	struct emmaprp_ctx *ctx = vb2_get_drv_priv(vb->vb2_queue);
	struct emmaprp_q_data *q_data;

	dprintk(ctx->dev, "type: %d\n", vb->vb2_queue->type);

	q_data = get_q_data(ctx, vb->vb2_queue->type);

	if (vb2_plane_size(vb, 0) < q_data->sizeimage) {
		dprintk(ctx->dev, "%s data will not fit into plane"
				  "(%lu < %lu)\n", __func__,
				  vb2_plane_size(vb, 0),
				  (long)q_data->sizeimage);
		return -EINVAL;
	}

	vb2_set_plane_payload(vb, 0, q_data->sizeimage);

	return 0;
}
