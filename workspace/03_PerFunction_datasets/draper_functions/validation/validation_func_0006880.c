vpdma_add_out_dtd(struct vpdma_desc_list *list, int width,
		const struct v4l2_rect *c_rect,
		const struct vpdma_data_format *fmt, dma_addr_t dma_addr,
		enum vpdma_channel chan, u32 flags)
{
	int priority = 0;
	int field = 0;
	int notify = 1;
	int channel, next_chan;
	struct v4l2_rect rect = *c_rect;
	int depth = fmt->depth;
	int stride;
	struct vpdma_dtd *dtd;

	channel = next_chan = chan_info[chan].num;

	if (fmt->type == VPDMA_DATA_FMT_TYPE_YUV &&
			fmt->data_type == DATA_TYPE_C420) {
		rect.height >>= 1;
		rect.top >>= 1;
		depth = 8;
	}

	stride = ALIGN((depth * width) >> 3, VPDMA_STRIDE_ALIGN);

	dma_addr += rect.top * stride + (rect.left * depth >> 3);

	dtd = list->next;
	WARN_ON((void *)(dtd + 1) > (list->buf.addr + list->buf.size));

	dtd->type_ctl_stride = dtd_type_ctl_stride(fmt->data_type,
					notify,
					field,
					!!(flags & VPDMA_DATA_FRAME_1D),
					!!(flags & VPDMA_DATA_EVEN_LINE_SKIP),
					!!(flags & VPDMA_DATA_ODD_LINE_SKIP),
					stride);
	dtd->w1 = 0;
	dtd->start_addr = (u32) dma_addr;
	dtd->pkt_ctl = dtd_pkt_ctl(!!(flags & VPDMA_DATA_MODE_TILED),
				DTD_DIR_OUT, channel, priority, next_chan);
	dtd->desc_write_addr = dtd_desc_write_addr(0, 0, 0, 0);
	dtd->max_width_height = dtd_max_width_height(MAX_OUT_WIDTH_1920,
					MAX_OUT_HEIGHT_1080);
	dtd->client_attr0 = 0;
	dtd->client_attr1 = 0;

	list->next = dtd + 1;

	dump_dtd(dtd);
}
