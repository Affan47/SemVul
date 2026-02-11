enc_mtu_req(uint16_t mtu, uint8_t *pdu, int len)
{
	const uint16_t min_len = sizeof(pdu[0]) + sizeof(mtu);

	if (pdu == NULL)
		return 0;

	if (len < min_len)
		return 0;

	pdu[0] = ATT_OP_MTU_REQ;
	att_put_u16(mtu, &pdu[1]);

	return min_len;
}
