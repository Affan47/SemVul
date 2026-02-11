ReplyGetSecurityCodeStatus(int messagetype, unsigned char *buffer, int length, gn_data *data, struct gn_statemachine *state)
{
	at_line_buffer buf;
	char *pos;
	gn_error error;

	if ((error = at_error_get(buffer, state)) != GN_ERR_NONE) return error;

	buf.line1 = buffer + 1;
	buf.length= length;
	splitlines(&buf);

	if (data->security_code && !strncmp(buf.line1, "AT+CPIN", 7)) {
		if (strncmp(buf.line2, "+CPIN: ", 7)) {
			data->security_code->type = 0;
			return GN_ERR_INTERNALERROR;
		}

		pos = 7 + buf.line2;

		if (!strncmp(pos, "READY", 5)) {
			data->security_code->type = GN_SCT_None;
			return GN_ERR_NONE;
		}

		if (!strncmp(pos, "SIM ", 4)) {
			pos += 4;
			if (!strncmp(pos, "PIN2", 4)) {
				data->security_code->type = GN_SCT_Pin2;
			}
			if (!strncmp(pos, "PUK2", 4)) {
				data->security_code->type = GN_SCT_Puk2;
			}
			if (!strncmp(pos, "PIN", 3)) {
				data->security_code->type = GN_SCT_Pin;
			}
			if (!strncmp(pos, "PUK", 3)) {
				data->security_code->type = GN_SCT_Puk;
			}
		}
	}
	return GN_ERR_NONE;
}
