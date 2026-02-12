ssize_t packet_get(int fd, struct gps_packet_t *lexer)

{
    ssize_t recvd;


    errno = 0;
    recvd = read(fd, lexer->inbuffer + lexer->inbuflen,
		 sizeof(lexer->inbuffer) - (lexer->inbuflen));

    if (recvd == -1) {
	if ((errno == EAGAIN) || (errno == EINTR)) {
	    gpsd_report(LOG_RAW + 2, "no bytes ready\n");
	    recvd = 0;

	} else {
	    gpsd_report(LOG_RAW + 2, "errno: %s\n", strerror(errno));
	    return -1;
	}
    } else {
	if (lexer->debug >= LOG_RAW+1)
	    gpsd_report(LOG_RAW + 1,
			"Read %zd chars to buffer offset %zd (total %zd): %s\n",
			recvd, lexer->inbuflen, lexer->inbuflen + recvd,
			gpsd_packetdump((char *)lexer->inbufptr, (size_t) recvd));
	lexer->inbuflen += recvd;
    }
    gpsd_report(LOG_SPIN, "packet_get() fd %d -> %zd (%d)\n",
		fd, recvd, errno);


    if (recvd <= 0 && packet_buffered_input(lexer) <= 0)
	return recvd;


    packet_parse(lexer);


    if (sizeof(lexer->inbuffer) == (lexer->inbuflen)) {

	packet_discard(lexer);
	lexer->state = GROUND_STATE;
    }


    if (lexer->outbuflen > 0)
	return (ssize_t) lexer->outbuflen;
    else


	return recvd;
}
