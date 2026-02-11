drv_LEDMatrix_blit(const int row, const int col, const int height, const int width)
{
    int r, c, i;
    fd_set rfds;
    struct timeval tv;
    unsigned char reply[256];
    struct sockaddr_in cli_addr;
    socklen_t fromlen;
    int ack = 0;
    int timeout = 10;

    for (r = row; r < row + height; r++) {
	for (c = col; c < col + width; c++) {


	    unsigned char color = 0;
	    RGBA p = drv_generic_graphic_rgb(r, c);
	    if (p.G >= 128)
		color |= 0x80;
	    if (p.R >= 128)
		color |= 0x40;


	    tx_buffer[1 + 20 * r + c / 4] &= ~(0xc0 >> (2 * (c & 3)));
	    tx_buffer[1 + 20 * r + c / 4] |= color >> (2 * (c & 3));
	}
    }


    tx_buffer[0] = DSP_CMD_IMAGE;

    do {

	if ((sendto(sock, tx_buffer, DSP_MEM + 1, 0, (struct sockaddr *) &dsp_addr, sizeof(dsp_addr))) != DSP_MEM + 1)
	    error("%s: sendto error on socket", Name);


	FD_ZERO(&rfds);
	FD_SET(sock, &rfds);
	tv.tv_sec = 0;
	tv.tv_usec = 100000;


	if ((i = select(FD_SETSIZE, &rfds, NULL, NULL, &tv)) < 0) {
	    info("%s: Select error: %s", Name, strerror(errno));
	}

	if (FD_ISSET(sock, &rfds)) {

	    fromlen = sizeof(dsp_addr);
	    i = recvfrom(sock, reply, sizeof(reply), 0, (struct sockaddr *) &cli_addr, &fromlen);
	    if (i < 0) {
		info("%s: Receive error: %s", Name, strerror(errno));
	    } else {
		if ((i == 2) && (reply[0] == DSP_CMD_ACK) && (reply[1] == DSP_CMD_IMAGE)) {
		    ack = 1;
		} else if ((i > 1) && (reply[0] == DSP_CMD_IR)) {


		} else {
		    info("%s: Unexpected reply message", Name);
		}
	    }
	}
	timeout--;
    } while ((!ack) && (timeout > 0));

    if (timeout == 0) {
	error("%s: display reply timeout", Name);
    }
}
