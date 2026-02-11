P3110_IncomingCall(int messagetype, unsigned char *message, int length, gn_data *data, struct gn_statemachine *state)
{
	int     count;
	char    buffer[256];


	for (count = 0; count < message[4]; count ++) {
		buffer[count] = message[5 + count];
	}
	buffer[count] = 0x00;


	dprintf("Incoming call - Type: %s. %02x, Number %s.\n",
		(message[2] == 0x05 ? "Voice":"Data?"), message[3], buffer);

	return GN_ERR_NONE;
}
