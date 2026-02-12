static void *vidtv_s302m_encode(struct vidtv_encoder *e)
{
	struct vidtv_s302m_ctx *ctx = e->ctx;


	vidtv_s302m_access_unit_destroy(e);
	vidtv_s302m_alloc_au(e);

	if (e->sync && e->sync->is_video_encoder) {
		vidtv_s302m_compute_sample_count_from_video(e);
		vidtv_s302m_compute_pts_from_video(e);
	} else {
		e->access_units->num_samples = FF_S302M_DEFAULT_NUM_FRAMES;
		e->access_units->pts = (ctx->au_count * FF_S302M_DEFAULT_PTS_INCREMENT) +
				       FF_S302M_DEFAULT_PTS_OFFSET;
	}

	vidtv_s302m_write_frames(e);

	return e->encoder_buf;
}
