static void find_good_pkt_pointers(struct bpf_verifier_state *vstate,
				   struct bpf_reg_state *dst_reg,
				   enum bpf_reg_type type,
				   bool range_right_open)
{
	int new_range, i;

	if (dst_reg->off < 0 ||
	    (dst_reg->off == 0 && range_right_open))

		return;

	if (dst_reg->umax_value > MAX_PACKET_OFF ||
	    dst_reg->umax_value + dst_reg->off > MAX_PACKET_OFF)


		return;

	new_range = dst_reg->off;
	if (range_right_open)
		new_range++;


	for (i = 0; i <= vstate->curframe; i++)
		__find_good_pkt_pointers(vstate->frame[i], dst_reg, type,
					 new_range);
}
