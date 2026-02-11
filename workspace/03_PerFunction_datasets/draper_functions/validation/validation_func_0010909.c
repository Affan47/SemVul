zoran_feed_stat_com (struct zoran *zr)
{


	int frame, i, max_stat_com;

	max_stat_com =
	    (zr->jpg_settings.TmpDcm ==
	     1) ? BUZ_NUM_STAT_COM : (BUZ_NUM_STAT_COM >> 1);

	while ((zr->jpg_dma_head - zr->jpg_dma_tail) < max_stat_com &&
	       zr->jpg_dma_head < zr->jpg_que_head) {

		frame = zr->jpg_pend[zr->jpg_dma_head & BUZ_MASK_FRAME];
		if (zr->jpg_settings.TmpDcm == 1) {

			i = (zr->jpg_dma_head -
			     zr->jpg_err_shift) & BUZ_MASK_STAT_COM;
			if (!(zr->stat_com[i] & cpu_to_le32(1)))
				break;
			zr->stat_com[i] =
			    cpu_to_le32(zr->jpg_buffers.buffer[frame].jpg.frag_tab_bus);
		} else {

			i = ((zr->jpg_dma_head -
			      zr->jpg_err_shift) & 1) * 2;
			if (!(zr->stat_com[i] & cpu_to_le32(1)))
				break;
			zr->stat_com[i] =
			    cpu_to_le32(zr->jpg_buffers.buffer[frame].jpg.frag_tab_bus);
			zr->stat_com[i + 1] =
			    cpu_to_le32(zr->jpg_buffers.buffer[frame].jpg.frag_tab_bus);
		}
		zr->jpg_buffers.buffer[frame].state = BUZ_STATE_DMA;
		zr->jpg_dma_head++;

	}
	if (zr->codec_mode == BUZ_MODE_MOTION_DECOMPRESS)
		zr->jpg_queued_num++;
}
