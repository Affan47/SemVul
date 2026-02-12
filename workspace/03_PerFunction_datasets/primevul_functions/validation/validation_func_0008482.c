static void ov511_pkt_scan(struct gspca_dev *gspca_dev,
			u8 *in,
			int len)
{
	struct sd *sd = (struct sd *) gspca_dev;


	if (!(in[0] | in[1] | in[2] | in[3] | in[4] | in[5] | in[6] | in[7]) &&
	    (in[8] & 0x08)) {
		ov51x_handle_button(gspca_dev, (in[8] >> 2) & 1);
		if (in[8] & 0x80) {

			if ((in[9] + 1) * 8 != gspca_dev->pixfmt.width ||
			    (in[10] + 1) * 8 != gspca_dev->pixfmt.height) {
				gspca_err(gspca_dev, "Invalid frame size, got: %dx%d, requested: %dx%d\n",
					  (in[9] + 1) * 8, (in[10] + 1) * 8,
					  gspca_dev->pixfmt.width,
					  gspca_dev->pixfmt.height);
				gspca_dev->last_packet_type = DISCARD_PACKET;
				return;
			}

			gspca_frame_add(gspca_dev, LAST_PACKET, in, 11);
			return;
		} else {

			gspca_frame_add(gspca_dev, FIRST_PACKET, in, 0);
			sd->packet_nr = 0;
		}
	}


	len--;


	gspca_frame_add(gspca_dev, INTER_PACKET, in, len);
}
