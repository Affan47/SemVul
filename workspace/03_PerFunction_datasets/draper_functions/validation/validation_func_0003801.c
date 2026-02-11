__handle_incoming_msg(struct read_msg_data *udata,
	unsigned char *buf)
{
	uint16_t len = GUINT16_FROM_LE(((buf[5] & 0xf) << 8) | buf[6]);
	uint16_t computed_crc = udf_crc(buf + 4, len + 3);
	uint16_t msg_crc = GUINT16_FROM_LE((buf[len + 8] << 8) | buf[len + 7]);
	unsigned char *retdata = NULL;
	unsigned char code_a, code_b;

	if (computed_crc != msg_crc) {
		fp_err("CRC failed, got %04x expected %04x", msg_crc, computed_crc);
		return -1;
	}

	code_a = buf[4];
	code_b = buf[5] & 0xf0;
	len = GUINT16_FROM_LE(((buf[5] & 0xf) << 8) | buf[6]);
	fp_dbg("A=%02x B=%02x len=%d", code_a, code_b, len);

	if (code_a && !code_b) {

		fp_dbg("cmd %x from device to driver", code_a);

		if (code_a == 0x08) {
			int r;
			fp_dbg("device busy, send busy-ack");
			r = busy_ack_retry_read(udata);
			return (r < 0) ? r : 1;
		}

		if (len > 0) {
			retdata = g_malloc(len);
			memcpy(retdata, buf + 7, len);
		}
		udata->callback(udata->dev, READ_MSG_CMD, code_a, 0, retdata, len,
			udata->user_data);
		g_free(retdata);
	} else if (!code_a) {

		unsigned char *innerbuf = buf + 7;
		unsigned char _subcmd;
		uint16_t innerlen;

		if (len < 6) {
			fp_err("cmd response too short (%d)", len);
			return -1;
		}
		if (innerbuf[0] != 0x28) {
			fp_err("cmd response without 28 byte?");
			return -1;
		}


		if (innerbuf[3] || innerbuf[4])
			fp_dbg("non-zero bytes in cmd response");

		innerlen = innerbuf[1] | (innerbuf[2] << 8);
		innerlen = GUINT16_FROM_LE(innerlen) - 3;
		_subcmd = innerbuf[5];
		fp_dbg("device responds to subcmd %x with %d bytes", _subcmd, innerlen);
		if (innerlen > 0) {
			retdata = g_malloc(innerlen);
			memcpy(retdata, innerbuf + 6, innerlen);
		}
		udata->callback(udata->dev, READ_MSG_RESPONSE, code_b, _subcmd,
			retdata, innerlen, udata->user_data);
		g_free(retdata);
	} else {
		fp_err("don't know how to handle this message");
		return -1;
	}
	return 0;
}
