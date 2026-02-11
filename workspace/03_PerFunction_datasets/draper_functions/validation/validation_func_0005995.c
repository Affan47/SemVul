knot_response_set_rcode(knot_packet_t *response, short rcode)
{
	if (response == NULL) {
		return;
	}

	uint8_t flags = knot_wire_get_flags2(response->wireformat);
	knot_wire_flags_set_rcode(&flags, rcode);
	knot_wire_set_flags2(response->wireformat, flags);
}
