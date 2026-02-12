static uint8_t *bgp_notify_encapsulate_hard_reset(uint8_t code, uint8_t subcode,
						  uint8_t *data, size_t datalen)
{
	uint8_t *message = XCALLOC(MTYPE_BGP_NOTIFICATION, datalen + 2);


	message[0] = code;

	message[1] = subcode;

	if (datalen)
		memcpy(message + 2, data, datalen);

	return message;
}
