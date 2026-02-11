NK6510_IncomingRadio(int messagetype, unsigned char *message, int length, gn_data *data, struct gn_statemachine *state)
{


	switch (message[3]) {
	case 0x02:

		return GN_ERR_NONE;
		break;
	default:
		break;
	}

	return GN_ERR_NOTIMPLEMENTED;
}
