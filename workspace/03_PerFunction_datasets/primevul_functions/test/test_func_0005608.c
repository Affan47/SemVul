static GF_Err isoffin_reconfigure(GF_Filter *filter, ISOMReader *read, const char *next_url)
{
	const GF_PropertyValue *prop;
	u32 i, count;
	Bool is_new_mov = GF_FALSE;
	u64 tfdt;

	GF_ISOSegOpenMode flags=0;
	GF_Err e;

	prop = gf_filter_pid_get_property(read->pid, GF_PROP_PID_FILE_CACHED);
	if (prop && prop->value.boolean)
		read->input_loaded = GF_TRUE;

	read->refresh_fragmented = GF_FALSE;
	read->full_segment_flush = GF_TRUE;
	GF_LOG(GF_LOG_DEBUG, GF_LOG_DASH, ("[IsoMedia] reconfigure triggered, URL %s\n", next_url));


	switch (gf_isom_probe_file_range(next_url, read->start_range, read->end_range)) {

	case 3:
		gf_isom_release_segment(read->mov, 1);
		gf_isom_reset_fragment_info(read->mov, GF_TRUE);

		if (read->no_order_check) flags |= GF_ISOM_SEGMENT_NO_ORDER_FLAG;


#if 0
		if (scalable_segment) flags |= GF_ISOM_SEGMENT_SCALABLE_FLAG;
#endif
		e = gf_isom_open_segment(read->mov, next_url, read->start_range, read->end_range, flags);
		if (!read->input_loaded && (e==GF_ISOM_INCOMPLETE_FILE)) {
			e = GF_OK;
		}


		if (!read->start_range && !read->end_range)
			read->refresh_fragmented = GF_TRUE;
		read->seg_name_changed = GF_TRUE;

		for (i=0; i<gf_list_count(read->channels); i++) {
			ISOMChannel *ch = gf_list_get(read->channels, i);
			if (ch->last_state==GF_EOS)
				ch->last_state=GF_OK;
		}

#ifndef GPAC_DISABLE_LOG
		if (e<0) {
			GF_LOG(GF_LOG_ERROR, GF_LOG_DASH, ("[IsoMedia] Error opening new segment %s at UTC "LLU": %s\n", next_url, gf_net_get_utc(), gf_error_to_string(e) ));
		} else if (read->end_range) {
			GF_LOG(GF_LOG_DEBUG, GF_LOG_DASH, ("[IsoMedia] Playing new range in %s: "LLU"-"LLU"\n", next_url, read->start_range, read->end_range));
		} else {
			GF_LOG(GF_LOG_DEBUG, GF_LOG_DASH, ("[IsoMedia] playing new segment %s\n", next_url));
		}
#endif
		break;

	case 2:
	case 1:


		tfdt = gf_isom_get_smooth_next_tfdt(read->mov, 1);
		GF_LOG(GF_LOG_DEBUG, GF_LOG_DASH, ("[IsoMedia] Switching between files - opening new init segment %s (time offset="LLU") - range "LLU"-"LLU"\n", next_url, tfdt, read->start_range, read->end_range));

		if (gf_isom_is_smooth_streaming_moov(read->mov)) {
			char *tfdt_val = strstr(next_url, "tfdt=");

			if (tfdt_val) {
				sprintf(tfdt_val+5, LLX, tfdt);
			} else {
				GF_LOG(GF_LOG_WARNING, GF_LOG_DASH, ("[IsoMedia] Error finding init time for init segment %s at UTC "LLU"\n", next_url, gf_net_get_utc() ));
			}
		}

		if (read->mov) gf_isom_close(read->mov);
		e = gf_isom_open_progressive(next_url, read->start_range, read->end_range, read->sigfrag, &read->mov, &read->missing_bytes);


		if (!read->input_loaded && (e==GF_ISOM_INCOMPLETE_FILE)) {
			read->src_crc = 0;
			read->moov_not_loaded = 2;
			return GF_OK;
		}

		read->moov_not_loaded = 0;
		if (e < 0) {
			GF_LOG(GF_LOG_ERROR, GF_LOG_DASH, ("[IsoMedia] Error opening init segment %s at UTC "LLU": %s\n", next_url, gf_net_get_utc(), gf_error_to_string(e) ));
		}
		if (read->sigfrag)
			gf_isom_enable_traf_map_templates(read->mov);

		is_new_mov = GF_TRUE;
		break;

	case 4:
		return GF_OK;
	default:
		if (!read->mov) {
            return GF_NOT_SUPPORTED;
		}
        e = GF_ISOM_INVALID_FILE;
        break;
	}

	gf_filter_post_process_task(filter);

	count = gf_list_count(read->channels);

	if (e<0) {
		count = gf_list_count(read->channels);
		gf_isom_release_segment(read->mov, 1);
        read->invalid_segment = GF_TRUE;

		gf_isom_reset_fragment_info(read->mov, GF_FALSE);
		for (i=0; i<count; i++) {
			ISOMChannel *ch = gf_list_get(read->channels, i);
            if (ch) {
                ch->sample_num = 0;
                ch->eos_sent = GF_FALSE;
            }
		}
        GF_LOG(GF_LOG_WARNING, GF_LOG_DASH, ("[IsoMedia] Error opening current segment %s: %s\n", next_url, gf_error_to_string(e) ));
		return GF_OK;
	}

	if (!read->input_loaded) {
		GF_LOG(GF_LOG_DEBUG, GF_LOG_DASH, ("[IsoMedia] Opening current segment in progressive mode (download in progress)\n"));
	} else {
		GF_LOG(GF_LOG_DEBUG, GF_LOG_DASH, ("[IsoMedia] Opening current segment in non-progressive mode (completely downloaded)\n"));
	}

	isor_check_producer_ref_time(read);

	for (i=0; i<count; i++) {
		ISOMChannel *ch = gf_list_get(read->channels, i);
		ch->last_state = GF_OK;
		ch->eos_sent = GF_FALSE;


#if 0
		if (ch->base_track) {
			if (scalable_segment)
				trackID = gf_isom_get_highest_track_in_scalable_segment(read->mov, ch->base_track);
				if (trackID) {
					ch->track_id = trackID;
					ch->track = gf_isom_get_track_by_id(read->mov, ch->track_id);
				}
			} else {
				ch->track = ch->base_track;
				ch->track_id = gf_isom_get_track_id(read->mov, ch->track);
			}
		}
#endif

		GF_LOG(GF_LOG_DEBUG, GF_LOG_DASH, ("[IsoMedia] Track %d - cur sample %d - new sample count %d\n", ch->track, ch->sample_num, gf_isom_get_sample_count(ch->owner->mov, ch->track) ));


		if (is_new_mov) {
			ch->track = gf_isom_get_track_by_id(read->mov, ch->track_id);
			if (!ch->track) {
				if (gf_isom_get_track_count(read->mov)==1) {
					GF_LOG(GF_LOG_DEBUG, GF_LOG_DASH, ("[IsoMedia] Mismatch between track IDs of different representations\n"));
					ch->track = 1;
				} else {
					GF_LOG(GF_LOG_ERROR, GF_LOG_DASH, ("[IsoMedia] Mismatch between track IDs of different representations\n"));
				}
			}


			ch->sample_num = 0;

			if (!ch->last_sample_desc_index)
				ch->last_sample_desc_index = 1;

			isor_update_channel_config(ch);


			gf_isom_set_nalu_extract_mode(read->mov, ch->track, ch->nalu_extract_mode);

			if (ch->is_cenc) {
				isor_set_crypt_config(ch);
			}
		}

		ch->last_state = GF_OK;
	}
