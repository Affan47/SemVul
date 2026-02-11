do_nvtflush(int mode)
{
	int purgemode;

	print_action("do_nvtflush");
	switch (Nvt.state) {
	case NVT_OPER:
	case NVT_WAITPTYWR:
		switch (mode) {
		case OPFLUSH_IN:
			purgemode = COM_PURGE_RECV;
			break;
		case OPFLUSH_OUT:
			purgemode = COM_PURGE_XMIT;
			break;
		case OPFLUSH_IO:
		default:
			purgemode = COM_PURGE_BOTH;
			break;
		}

		tel_putcmd(USR_COM_PURGE_DATA, purgemode);
		if (Nvt.state == NVT_OPER) {
			NVT_SETSTATE("do_nvtflush", NVT_WAITRASCM);
		} else {
			NVT_SETSTATE("do_nvtflush", NVT_WAITRCPW);
		}
		break;
	default:
		do_nvterror("do_nvtflush");
		break;
	}
}
