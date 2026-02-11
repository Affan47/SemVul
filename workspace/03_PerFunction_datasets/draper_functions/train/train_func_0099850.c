got_packet(u_char *args, const struct pcap_pkthdr *header,
		const u_char *packetReceived) {
	static int count = 1;
	u_char *packet;
	struct data_to_pass data;
	u_int numBytes;
	u_int dataLength;
	PRINT_DEBUG("Packet number %d: has been captured \n", count);

	if (header->caplen != header->len) {
		PRINT_DEBUG("Snaplen value is not enough to capture the whole packet as it is on wire \n");
		exit(1);
	}


	dataLength = header->caplen;

	print_frame(packetReceived, dataLength);
	fflush(stdout);
	numBytes = write(income_pipe_fd, &dataLength, sizeof(u_int));
	if (numBytes <= 0) {
		PRINT_DEBUG("numBytes written %d\n", numBytes);

		return;
	}

	numBytes = write(income_pipe_fd, packetReceived, dataLength);

	if (numBytes <= 0) {
		PRINT_DEBUG("numBytes written %d\n", numBytes);

		return;
	}
	PRINT_DEBUG("A frame of length %d has been captured \n", numBytes);

	capture_count++;

	return;

}
