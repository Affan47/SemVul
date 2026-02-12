void ikev1_init_out_pbs_echo_hdr(struct msg_digest *md, bool enc,
				 pb_stream *output_stream, uint8_t *output_buffer,
				 size_t sizeof_output_buffer,
				 pb_stream *rbody)
{
	struct isakmp_hdr hdr = md->hdr;


	init_out_pbs(output_stream, output_buffer, sizeof_output_buffer,
		     "reply packet");

	hdr.isa_flags = 0;
	if (enc)
		hdr.isa_flags |= ISAKMP_FLAGS_v1_ENCRYPTION;

	if (impair.send_bogus_isakmp_flag) {
		hdr.isa_flags |= ISAKMP_FLAGS_RESERVED_BIT6;
	}


	hdr.isa_np = 0;

	passert(out_struct(&hdr, &isakmp_hdr_desc, output_stream, rbody));
}
