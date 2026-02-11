encode_deliver_ack_report(const struct sms_deliver_ack_report *in,
						unsigned char *pdu,
						int *offset)
{
	unsigned char oct;

	oct = 0;

	if (in->udhi)
		oct |= 1 << 6;

	set_octet(pdu, offset, oct);

	set_octet(pdu, offset, in->pi);

	if (in->pi & 0x1)
		set_octet(pdu, offset, in->pid);

	if (in->pi & 0x2)
		set_octet(pdu, offset, in->dcs);

	if (in->pi & 0x4) {
		int ud_oct_len = sms_udl_in_bytes(in->udl, in->dcs);

		set_octet(pdu, offset, in->udl);
		memcpy(pdu + *offset, in->ud, ud_oct_len);
		*offset = *offset + ud_oct_len;
	}

	return TRUE;
}
