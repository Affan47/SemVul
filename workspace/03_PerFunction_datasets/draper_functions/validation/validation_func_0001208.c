musb_comp_channel_open(mud_channel *pc)
{
	int fd;
	enum HPMUD_RESULT stat = HPMUD_R_DEVICE_BUSY;


	switch (pc->index)
	{
		case HPMUD_EWS_CHANNEL:
			fd = FD_ff_1_1;
			break;
		case HPMUD_EWS_LEDM_CHANNEL:
			fd = FD_ff_4_1;
			break;
		case HPMUD_SOAPSCAN_CHANNEL:
			fd = FD_ff_2_1;
			break;
		case HPMUD_SOAPFAX_CHANNEL:
			fd = FD_ff_3_1;
			break;
		case HPMUD_MARVELL_SCAN_CHANNEL:
			fd = FD_ff_ff_ff;
			break;
		case HPMUD_MARVELL_FAX_CHANNEL:
			fd = FD_ff_1_0;
			break;
		case HPMUD_LEDM_SCAN_CHANNEL:
			fd = FD_ff_cc_0;
			break;
		case HPMUD_MARVELL_EWS_CHANNEL:
			fd = FD_ff_2_10;
			break;
		default:
			stat = HPMUD_R_INVALID_SN;
			BUG("invalid %s channel=%d\n", pc->sn, pc->index);
			goto bugout;
			break;
	}

	if (get_interface(libusb_dev, fd, &fd_table[fd]))
	{
		stat = HPMUD_R_INVALID_SN;
		BUG("invalid %s channel=%d\n", pc->sn, pc->index);
		goto bugout;
	}

	if (claim_interface(libusb_dev, &fd_table[fd]))
		goto bugout;

	pc->fd = fd;

	stat = HPMUD_R_OK;

bugout:
	return stat;
}
