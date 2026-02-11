print_sdp_stream(sdp_stream_cell_t *stream, int log_level)
{
	sdp_payload_attr_t *payload;

	LM_GEN1(log_level, "....stream[%d]:%p=>%p {%p} '%.*s' '%.*s:%.*s:%.*s' '%.*s' [%d] '%.*s' '%.*s:%.*s' (%d)=>%p '%.*s' '%.*s' '%.*s' '%.*s' '%.*s' '%.*s'\n",
		stream->stream_num, stream, stream->next,
		stream->p_payload_attr,
		stream->media.len, stream->media.s,
		stream->ip_addr.len, stream->ip_addr.s, stream->port.len, stream->port.s,
		stream->rtcp_port.len, stream->rtcp_port.s,
		stream->transport.len, stream->transport.s, stream->is_rtp,
		stream->payloads.len, stream->payloads.s,
		stream->bw_type.len, stream->bw_type.s, stream->bw_width.len, stream->bw_width.s,
		stream->payloads_num, stream->payload_attr,
		stream->sendrecv_mode.len, stream->sendrecv_mode.s,
		stream->ptime.len, stream->ptime.s,
		stream->path.len, stream->path.s,
		stream->max_size.len, stream->max_size.s,
		stream->accept_types.len, stream->accept_types.s,
		stream->accept_wrapped_types.len, stream->accept_wrapped_types.s);
	payload = stream->payload_attr;
	while (payload) {
		LM_GEN1(log_level, "......payload[%d]:%p=>%p p_payload_attr[%d]:%p '%.*s' '%.*s' '%.*s' '%.*s' '%.*s'\n",
			payload->payload_num, payload, payload->next,
			payload->payload_num, stream->p_payload_attr[payload->payload_num],
			payload->rtp_payload.len, payload->rtp_payload.s,
			payload->rtp_enc.len, payload->rtp_enc.s,
			payload->rtp_clock.len, payload->rtp_clock.s,
			payload->rtp_params.len, payload->rtp_params.s,
			payload->fmtp_string.len, payload->fmtp_string.s);
		payload=payload->next;
	}
}
