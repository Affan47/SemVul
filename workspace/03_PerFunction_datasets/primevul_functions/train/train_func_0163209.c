void tw5864_prepare_frame_headers(struct tw5864_input *input)
{
	struct tw5864_buf *vb = input->vb;
	u8 *dst;
	size_t dst_space;
	unsigned long flags;

	if (!vb) {
		spin_lock_irqsave(&input->slock, flags);
		if (list_empty(&input->active)) {
			spin_unlock_irqrestore(&input->slock, flags);
			input->vb = NULL;
			return;
		}
		vb = list_first_entry(&input->active, struct tw5864_buf, list);
		list_del(&vb->list);
		spin_unlock_irqrestore(&input->slock, flags);
	}

	dst = vb2_plane_vaddr(&vb->vb.vb2_buf, 0);
	dst_space = vb2_plane_size(&vb->vb.vb2_buf, 0);


	if (WARN_ON_ONCE(dst_space < 128))
		return;


	if (input->frame_gop_seqno == 0)
		tw5864_h264_put_stream_header(&dst, &dst_space, input->qp,
					      input->width, input->height);


	tw5864_h264_put_slice_header(&dst, &dst_space, input->h264_idr_pic_id,
				     input->frame_gop_seqno,
				     &input->tail_nb_bits, &input->tail);
	input->vb = vb;
	input->buf_cur_ptr = dst;
	input->buf_cur_space_left = dst_space;
}
