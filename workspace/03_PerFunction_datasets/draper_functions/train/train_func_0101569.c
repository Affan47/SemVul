sf_set_reply_mode(unsigned char buf[], int buflen)
{
	unsigned char partition;

	if (buflen < 5) {
		trace_ds(" error: wrong field length %d\n", buflen);
		return PDS_BAD_CMD;
	}

	partition = buf[3];
	trace_ds("(0x%02x)", partition);
	if (partition != 0x00) {
		trace_ds(" error: illegal partition\n");
		return PDS_BAD_CMD;
	}

	switch (buf[4]) {
	    case SF_SRM_FIELD:
		trace_ds(" Field\n");
		break;
	    case SF_SRM_XFIELD:
		trace_ds(" ExtendedField\n");
		break;
	    case SF_SRM_CHAR:
		trace_ds(" Character");
		break;
	    default:
		trace_ds(" unknown mode 0x%02x\n", buf[4]);
		return PDS_BAD_CMD;
	}
	return PDS_OKAY_NO_OUTPUT;
}
