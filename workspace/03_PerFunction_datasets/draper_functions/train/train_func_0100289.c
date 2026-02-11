par96_rx(struct net_device *dev, struct baycom_state *bc)
{
	int i;
	unsigned int data, mask, mask2, descx;
	struct parport *pp = bc->pdev->port;


	for(data = i = 0; i < PAR96_BURSTBITS; i++) {
		bc->modem.par96.descram = (bc->modem.par96.descram << 1);
		if (pp->ops->read_status(pp) & PAR96_RXBIT)
			bc->modem.par96.descram |= 1;
		descx = bc->modem.par96.descram ^
			(bc->modem.par96.descram >> 1);

		pp->ops->write_data(pp, PAR97_POWER | PAR96_PTT);
		descx ^= ((descx >> PAR96_DESCRAM_TAPSH1) ^
			  (descx >> PAR96_DESCRAM_TAPSH2));
		data >>= 1;
		if (!(descx & 1))
			data |= 0x8000;
		pp->ops->write_data(pp, PAR97_POWER | PAR96_PTT | PAR96_BURST);
	}
	hdlcdrv_putbits(&bc->hdrv, data);


	if (bc->options & BAYCOM_OPTIONS_SOFTDCD) {
		bc->modem.par96.dcd_shreg = (bc->modem.par96.dcd_shreg >> 16)
			| (data << 16);

		for(mask = 0x1fe00, mask2 = 0xfc00, i = 0;
		    i < PAR96_BURSTBITS; i++, mask <<= 1, mask2 <<= 1)
			if ((bc->modem.par96.dcd_shreg & mask) == mask2)
				bc->modem.par96.dcd_count = HDLCDRV_MAXFLEN+4;

		for(mask = 0x1fe00, mask2 = 0x1fe00, i = 0;
		    i < PAR96_BURSTBITS; i++, mask <<= 1, mask2 <<= 1)
			if (((bc->modem.par96.dcd_shreg & mask) == mask2) &&
			    (bc->modem.par96.dcd_count >= 0))
				bc->modem.par96.dcd_count -= HDLCDRV_MAXFLEN-10;

		if (bc->modem.par96.dcd_count >= 0)
			bc->modem.par96.dcd_count -= 2;
		hdlcdrv_setdcd(&bc->hdrv, bc->modem.par96.dcd_count > 0);
	} else {
		hdlcdrv_setdcd(&bc->hdrv, !!(pp->ops->read_status(pp) & PAR96_DCD));
	}
}
