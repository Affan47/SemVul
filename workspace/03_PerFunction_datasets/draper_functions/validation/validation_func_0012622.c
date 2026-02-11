handle_KHL_CH(struct ptype_action_args *parg)
{
	struct KHL_CH_data rdata;
	g2_packet_t *source = parg->source;
	g2_connection_t *connec = parg->connec;
	size_t remaining;
	union combo_addr addr;
	time_t when;
	bool ret_val = false;

	rdata.guid = NULL;

	if(unlikely(source->is_compound))
	{
		struct ptype_action_args cparg;
		bool keep_decoding;

		cparg = *parg;
		cparg.father = source;
		cparg.opaque = &rdata;
		do
		{
			g2_packet_t child_p;
			cparg.source = &child_p;
			child_p.more_bytes_needed = false;
			child_p.packet_decode = CHECK_CONTROLL_BYTE;
			keep_decoding = g2_packet_decode_from_packet(source, &child_p, 0);
			if(!keep_decoding) {
				logg_packet(STDLF, "KHL/NH/CH", "broken child");
				connec->flags.dismissed = true;
				break;
			}
			if(likely(child_p.packet_decode == DECODE_FINISHED))
				ret_val |= g2_packet_decide_spec_int(&cparg, KHL_CH_packet_dict);
		} while(keep_decoding && source->packet_decode != DECODE_FINISHED);
	}


	if(source->packet_decode != DECODE_FINISHED)
		return ret_val;


	remaining = buffer_remaining(source->data_trunk);

	if(8 == sizeof(time_t))
		when = local_time_now & (time_t)0xFFFFFFFF00000000ULL;
	else
		when = 0;

	if(10 == remaining ||
	   22 == remaining    )
	{
		char *data = buffer_start(source->data_trunk) + remaining - 4;
		uint32_t t;
		get_unaligned_endian(t, (uint32_t *)data, source->big_endian);
		source->data_trunk.limit -= 4;
		when |= (time_t)(t + connec->time_diff);
	}
	else if(26 == remaining ||
	        14 == remaining    )
	{
		char *data = buffer_start(source->data_trunk) + remaining - 8;
		uint64_t t;
		get_unaligned_endian(t, (uint64_t *)data, source->big_endian);
		source->data_trunk.limit -= 8;
		when = (time_t)(t + connec->time_diff);
	} else {
		logg_packet(STDLF, "/KHL/CH", "funny length");
		goto out;
	}

	if(read_na_from_packet(source, &addr, "/KHL/CH")) {
		g2_khl_add(&addr, when, false);
		if(rdata.guid)
			g2_guid_add(rdata.guid, &addr, when, GT_KHL);
	}

out:
	return ret_val;
}
