pkt_probe_settings(struct pktcdvd_device *pd)
{
	struct packet_command cgc;
	unsigned char buf[12];
	disc_information di;
	track_information ti;
	int ret, track;

	init_cdrom_command(&cgc, buf, sizeof(buf), CGC_DATA_READ);
	cgc.cmd[0] = GPCMD_GET_CONFIGURATION;
	cgc.cmd[8] = 8;
	ret = pkt_generic_packet(pd, &cgc);
	pd->mmc3_profile = ret ? 0xffff : buf[6] << 8 | buf[7];

	memset(&di, 0, sizeof(disc_information));
	memset(&ti, 0, sizeof(track_information));

	if ((ret = pkt_get_disc_info(pd, &di))) {
		pkt_err(pd, "failed get_disc\n");
		return ret;
	}

	if (!pkt_writable_disc(pd, &di))
		return -EROFS;

	pd->type = di.erasable ? PACKET_CDRW : PACKET_CDR;

	track = 1;
	if ((ret = pkt_get_track_info(pd, track, 1, &ti))) {
		pkt_err(pd, "failed get_track\n");
		return ret;
	}

	if (!pkt_writable_track(pd, &ti)) {
		pkt_err(pd, "can't write to this track\n");
		return -EROFS;
	}


	pd->settings.size = be32_to_cpu(ti.fixed_packet_size) << 2;
	if (pd->settings.size == 0) {
		pkt_notice(pd, "detected zero packet size!\n");
		return -ENXIO;
	}
	if (pd->settings.size > PACKET_MAX_SECTORS) {
		pkt_err(pd, "packet size is too big\n");
		return -EROFS;
	}
	pd->settings.fp = ti.fp;
	pd->offset = (be32_to_cpu(ti.track_start) << 2) & (pd->settings.size - 1);

	if (ti.nwa_v) {
		pd->nwa = be32_to_cpu(ti.next_writable);
		set_bit(PACKET_NWA_VALID, &pd->flags);
	}


	if (ti.lra_v) {
		pd->lra = be32_to_cpu(ti.last_rec_address);
		set_bit(PACKET_LRA_VALID, &pd->flags);
	} else {
		pd->lra = 0xffffffff;
		set_bit(PACKET_LRA_VALID, &pd->flags);
	}


	pd->settings.link_loss = 7;
	pd->settings.write_type = 0;
	pd->settings.track_mode = ti.track_mode;


	switch (ti.data_mode) {
		case PACKET_MODE1:
			pd->settings.block_mode = PACKET_BLOCK_MODE1;
			break;
		case PACKET_MODE2:
			pd->settings.block_mode = PACKET_BLOCK_MODE2;
			break;
		default:
			pkt_err(pd, "unknown data mode\n");
			return -EROFS;
	}
	return 0;
}
