dtcs033_pkt_scan(struct gspca_dev *gspca_dev,
			u8 *data,
			int len)
{

	if (len != DT_COLS*512) {
		gspca_dev->last_packet_type = DISCARD_PACKET;

		return;
	}


	gspca_frame_add(gspca_dev, FIRST_PACKET, NULL, 0);
	gspca_frame_add(gspca_dev, INTER_PACKET,
		data + 16*DT_COLS,
		len  - 32*DT_COLS);
	gspca_frame_add(gspca_dev, LAST_PACKET,  NULL, 0);

	return;
}
