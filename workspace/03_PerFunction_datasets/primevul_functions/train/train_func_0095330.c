static void adts_dmx_check_pid(GF_Filter *filter, GF_ADTSDmxCtx *ctx)
{
	GF_BitStream *dsi;
	Bool use_implicit=GF_FALSE;
	u8 *dsi_b;
	u32 i, sbr_sr_idx, dsi_s, sr, sbr_sr, codecid, timescale=0;

	if (!ctx->opid) {
		ctx->opid = gf_filter_pid_new(filter);
		gf_filter_pid_copy_properties(ctx->opid, ctx->ipid);
		adts_dmx_check_dur(filter, ctx);
	}

	if ((ctx->sr_idx == ctx->hdr.sr_idx) && (ctx->nb_ch == ctx->hdr.nb_ch)
		&& (ctx->is_mp2 == ctx->hdr.is_mp2) && (ctx->profile == ctx->hdr.profile) ) return;


	gf_filter_pid_set_property(ctx->opid, GF_PROP_PID_STREAM_TYPE, & PROP_UINT( GF_STREAM_AUDIO));
	gf_filter_pid_set_property(ctx->opid, GF_PROP_PID_CODECID, & PROP_UINT( GF_CODECID_AAC_MPEG4));
	gf_filter_pid_set_property(ctx->opid, GF_PROP_PID_SAMPLES_PER_FRAME, & PROP_UINT(ctx->frame_size) );
	gf_filter_pid_set_property(ctx->opid, GF_PROP_PID_UNFRAMED, & PROP_BOOL(GF_FALSE) );
	if (ctx->is_file && ctx->index) {
		gf_filter_pid_set_property(ctx->opid, GF_PROP_PID_PLAYBACK_MODE, & PROP_UINT(GF_PLAYBACK_MODE_FASTFORWARD) );
	}

	if (ctx->duration.num)
		gf_filter_pid_set_property(ctx->opid, GF_PROP_PID_DURATION, & PROP_FRAC64(ctx->duration));


	ctx->is_mp2 = ctx->hdr.is_mp2;
	ctx->nb_ch = ctx->hdr.nb_ch;
	ctx->profile = ctx->hdr.profile;

	sr = GF_M4ASampleRates[ctx->hdr.sr_idx];
	if (!ctx->timescale) {

		if (ctx->cts && (ctx->sr_idx != ctx->hdr.sr_idx)) {
			ctx->cts *= sr;
			ctx->cts /= GF_M4ASampleRates[ctx->sr_idx];
		}
	}
	ctx->sr_idx = ctx->hdr.sr_idx;


	codecid = ctx->hdr.is_mp2 ? ctx->hdr.profile+GF_CODECID_AAC_MPEG2_MP-1 : GF_CODECID_AAC_MPEG4;
	gf_filter_pid_set_property(ctx->opid, GF_PROP_PID_CODECID, & PROP_UINT(codecid) );


	if (ctx->ps==AAC_SIGNAL_EXPLICIT) {
		ctx->sbr = AAC_SIGNAL_EXPLICIT;
	}

	if (ctx->hdr.is_mp2) {
		if (ctx->sbr == AAC_SIGNAL_EXPLICIT) ctx->sbr = AAC_SIGNAL_IMPLICIT;
		if (ctx->ps == AAC_SIGNAL_EXPLICIT) ctx->ps = AAC_SIGNAL_IMPLICIT;
	}

	dsi = gf_bs_new(NULL, 0, GF_BITSTREAM_WRITE);
	ctx->dts_inc = ctx->frame_size;

	if (!ctx->ovsbr) {
		sbr_sr = 0;
		sbr_sr_idx = 0;
		for (i=0; i<16; i++) {
			if (GF_M4ASampleRates[i] == (u32) 2*sr) {
				sbr_sr_idx = i;
				sbr_sr = 2*sr;
				break;
			}
		}
	} else {
		sbr_sr = sr;
		sbr_sr_idx = ctx->hdr.sr_idx;
	}

	ctx->acfg.base_object_type = ctx->hdr.profile;
	ctx->acfg.base_sr = sr;
	ctx->acfg.base_sr_index = ctx->hdr.sr_idx;
	ctx->acfg.nb_chan = ctx->hdr.nb_ch;
	ctx->acfg.sbr_object_type = 0;


	if  (ctx->acfg.nb_chan<=2) {
		if (ctx->ps==AAC_SIGNAL_EXPLICIT) {
			ctx->acfg.base_object_type = 29;
			ctx->acfg.sbr_object_type = ctx->hdr.profile;
			ctx->acfg.sbr_sr = sr;
			ctx->acfg.sbr_sr_index = ctx->acfg.base_sr_index;
		} else if (ctx->ps==AAC_SIGNAL_IMPLICIT) {
			use_implicit = GF_TRUE;
		}
	}

	if (ctx->sbr==AAC_SIGNAL_EXPLICIT) {

		if (ctx->acfg.base_object_type != 29)
			ctx->acfg.base_object_type = 5;
		ctx->acfg.sbr_object_type = ctx->hdr.profile;
		ctx->acfg.sbr_sr = sbr_sr;
		ctx->acfg.sbr_sr_index = sbr_sr_idx;
	} else if (ctx->sbr==AAC_SIGNAL_IMPLICIT) {
		sbr_sr = 0;
		use_implicit = GF_TRUE;
	} else {
		sbr_sr = 0;
	}
	ctx->acfg.audioPL = gf_m4a_get_profile(&ctx->acfg);


	if (sbr_sr) {
		ctx->dts_inc *= 2;
		sr = sbr_sr;
	}

	gf_m4a_write_config_bs(dsi, &ctx->acfg);
	gf_bs_align(dsi);


	if (use_implicit) {
		gf_bs_write_int(dsi, 0x2b7, 11);
		gf_bs_write_int(dsi, 5, 5);

		if (ctx->sbr==AAC_SIGNAL_IMPLICIT) {
			gf_bs_write_int(dsi, 1, 1);
			gf_bs_write_int(dsi, sbr_sr_idx, 4);
		} else {
			gf_bs_write_int(dsi, 0, 1);
		}
		if (ctx->ps==AAC_SIGNAL_IMPLICIT) {
			gf_bs_write_int(dsi, 0x548, 11);
			gf_bs_write_int(dsi, 1, 1);
		}
		gf_bs_align(dsi);
	}

	gf_bs_get_content(dsi, &dsi_b, &dsi_s);
	gf_bs_del(dsi);
	gf_filter_pid_set_property(ctx->opid, GF_PROP_PID_DECODER_CONFIG, & PROP_DATA_NO_COPY(dsi_b, dsi_s) );
	gf_filter_pid_set_property(ctx->opid, GF_PROP_PID_PROFILE_LEVEL, & PROP_UINT (ctx->acfg.audioPL) );
	gf_filter_pid_set_property(ctx->opid, GF_PROP_PID_SAMPLE_RATE, & PROP_UINT(sr));

	timescale = sr;
	if (ctx->ovsbr) timescale = 2*sr;

	gf_filter_pid_set_property(ctx->opid, GF_PROP_PID_TIMESCALE, & PROP_UINT(ctx->timescale ? ctx->timescale : timescale));
	gf_filter_pid_set_property(ctx->opid, GF_PROP_PID_NUM_CHANNELS, & PROP_UINT(ctx->nb_ch) );

	if (ctx->bitrate) {
		gf_filter_pid_set_property(ctx->opid, GF_PROP_PID_BITRATE, & PROP_UINT(ctx->bitrate));
	}

	if (ctx->id3_buffer_size) {
		id3dmx_flush(filter, ctx->id3_buffer, ctx->id3_buffer_size, ctx->opid, ctx->expart ? &ctx->vpid : NULL);
		ctx->id3_buffer_size = 0;
	}

}
