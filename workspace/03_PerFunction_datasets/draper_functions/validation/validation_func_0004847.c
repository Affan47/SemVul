_pack_block_info_req_msg(block_info_request_msg_t *msg, Buf buffer,
			 uint16_t protocol_version)
{
	if (protocol_version >= SLURM_2_5_PROTOCOL_VERSION) {
		pack_time(msg->last_update, buffer);
		pack16(msg->show_flags, buffer);
	} else {
		error("_pack_block_info_req_msg: protocol_version "
		      "%hu not supported", protocol_version);
	}
}
