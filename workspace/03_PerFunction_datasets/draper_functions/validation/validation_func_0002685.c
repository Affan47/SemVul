ntlmssp_output_restriction_encoding(NTLMSSP* ntlmssp)
{
	AV_PAIR *restrictions = &ntlmssp->av_pairs->Restrictions;
	STREAM* s = stream_new(0);

	uint8 machineID[32] =
		"\x3A\x15\x8E\xA6\x75\x82\xD8\xF7\x3E\x06\xFA\x7A\xB4\xDF\xFD\x43"
		"\x84\x6C\x02\x3A\xFD\x5A\x94\xFE\xCF\x97\x0F\x3D\x19\x2C\x38\x20";

	restrictions->value = xmalloc(48);
	restrictions->length = 48;

	s->data = restrictions->value;
	s->size = restrictions->length;
	s->p = s->data;

	stream_write_uint32(s, 48);
	stream_write_zero(s, 4);


	stream_write_uint8(s, 1);
	stream_write_zero(s, 3);

	stream_write_uint32(s, 0x20000000);
	stream_write(s, machineID, 32);

	xfree(s);
}
