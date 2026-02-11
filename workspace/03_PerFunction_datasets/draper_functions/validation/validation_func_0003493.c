drv_CF_send(const unsigned char cmd, const unsigned char len, const unsigned char *data)
{

    unsigned char buffer[26];
    unsigned short crc;
    struct timeval now, end;

    if (len > Payload) {
	error("%s: internal error: packet length %d exceeds payload size %d", Name, len, Payload);
	return;
    }

    buffer[0] = cmd;
    buffer[1] = len;
    memcpy(buffer + 2, data, len);
    crc = CRC(buffer, len + 2, 0xffff);
    buffer[len + 2] = LSB(crc);
    buffer[len + 3] = MSB(crc);

    drv_generic_serial_write((char *) buffer, len + 4);


    gettimeofday(&now, NULL);
    while (1) {

	usleep(1 * 1000);
	if (drv_CF_poll()) {
	    if (Packet.type == 0x01 && Packet.code == cmd) {

		if (0) {
		    gettimeofday(&end, NULL);
		    debug("%s: ACK after %ld usec", Name,
			  1000000 * (end.tv_sec - now.tv_sec) + end.tv_usec - now.tv_usec);
		}
		break;
	    } else {

		drv_CF_process_packet();
	    }
	}
	gettimeofday(&end, NULL);

	if ((1000000 * (end.tv_sec - now.tv_sec) + end.tv_usec - now.tv_usec) > 250 * 1000) {
	    error("%s: timeout waiting for response to cmd 0x%02x", Name, cmd);
	    break;
	}
    }
}
