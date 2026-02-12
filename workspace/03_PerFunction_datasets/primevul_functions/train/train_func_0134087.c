proto_is_protocol_enabled(const protocol_t *protocol)
{
	if (protocol == NULL)
		return FALSE;


	if (proto_is_pino(protocol))
		return proto_is_protocol_enabled(find_protocol_by_id(protocol->parent_proto_id));

	return protocol->is_enabled;
}
