static BOOL rdg_send_handshake(rdpRdg* rdg)
{
	wStream* s;
	BOOL status;
	s = Stream_New(NULL, 14);

	if (!s)
		return FALSE;

	Stream_Write_UINT16(s, PKT_TYPE_HANDSHAKE_REQUEST);
	Stream_Write_UINT16(s, 0);
	Stream_Write_UINT32(s, 14);
	Stream_Write_UINT8(s, 1);
	Stream_Write_UINT8(s, 0);
	Stream_Write_UINT16(s, 0);
	Stream_Write_UINT16(s, rdg->extAuth);
	Stream_SealLength(s);
	status = rdg_write_packet(rdg, s);
	Stream_Free(s, TRUE);

	if (status)
	{
		rdg->state = RDG_CLIENT_STATE_HANDSHAKE;
	}

	return status;
}
