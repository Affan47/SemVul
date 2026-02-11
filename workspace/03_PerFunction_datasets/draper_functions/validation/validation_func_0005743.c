main(int argc, char *argv[]) {
	if (argc < 2) {
		fprintf(stderr, "%s in.amr\n", argv[0]);
		return 1;
	}

	FILE* in = fopen(argv[1], "rb");
	if (!in) {
		perror(argv[1]);
		return 1;
	}
	char header[6];
	int n = fread(header, 1, 6, in);
	if (n != 6 || memcmp(header, "#!AMR\n", 6)) {
		fprintf(stderr, "Bad header\n");
		return 1;
	}

	WavWriter wav("out.wav", 8000, 16, 1);

	void* amr = Decoder_Interface_init();
	while (true) {
		uint8_t buffer[500];

		n = fread(buffer, 1, 1, in);
		if (n <= 0)
			break;

		int size = sizes[(buffer[0] >> 3) & 0x0f];
		if (size <= 0)
			break;
		n = fread(buffer + 1, 1, size, in);
		if (n != size)
			break;


		int16_t outbuffer[160];
		Decoder_Interface_Decode(amr, buffer, outbuffer, 0);


		uint8_t littleendian[320];
		uint8_t* ptr = littleendian;
		for (int i = 0; i < 160; i++) {
			*ptr++ = (outbuffer[i] >> 0) & 0xff;
			*ptr++ = (outbuffer[i] >> 8) & 0xff;
		}
		wav.writeData(littleendian, 320);
	}
	fclose(in);
	Decoder_Interface_exit(amr);
	return 0;
}
