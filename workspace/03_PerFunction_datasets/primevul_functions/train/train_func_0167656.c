static bool aivdm_decode(const char *buf, size_t buflen,
		  struct aivdm_context_t ais_contexts[AIVDM_CHANNELS],
		  struct ais_t *ais,
		  int debug)
{
#ifdef __UNUSED_DEBUG__
    char *sixbits[64] = {
	"000000", "000001", "000010", "000011", "000100",
	"000101", "000110", "000111", "001000", "001001",
	"001010", "001011", "001100", "001101", "001110",
	"001111", "010000", "010001", "010010", "010011",
	"010100", "010101", "010110", "010111", "011000",
	"011001", "011010", "011011", "011100", "011101",
	"011110", "011111", "100000", "100001", "100010",
	"100011", "100100", "100101", "100110", "100111",
	"101000", "101001", "101010", "101011", "101100",
	"101101", "101110", "101111", "110000", "110001",
	"110010", "110011", "110100", "110101", "110110",
	"110111", "111000", "111001", "111010", "111011",
	"111100", "111101", "111110", "111111",
    };
#endif
    int nfrags, ifrag, nfields = 0;
    unsigned char *field[NMEA_MAX*2];
    unsigned char fieldcopy[NMEA_MAX*2+1];
    unsigned char *data, *cp;
    unsigned char ch, pad;
    struct aivdm_context_t *ais_context;
    int i;

    if (buflen == 0)
	return false;


    gpsd_report(LOG_PROG, "AIVDM packet length %zd: %s\n", buflen, buf);


    memset(ais, 0, sizeof(*ais));


    if (strlen(buf) > sizeof(fieldcopy)-1) {
	gpsd_report(LOG_ERROR, "overlong AIVDM packet.\n");
	return false;
    }


    (void)strlcpy((char *)fieldcopy, buf, sizeof(fieldcopy));
    field[nfields++] = (unsigned char *)buf;
    for (cp = fieldcopy;
	 cp < fieldcopy + buflen; cp++)
	if (*cp == (unsigned char)',') {
	    *cp = '\0';
	    field[nfields++] = cp + 1;
	}


    if (nfields < 7) {
	gpsd_report(LOG_ERROR, "malformed AIVDM packet.\n");
	return false;
    }

    switch (field[4][0]) {

    case '\0':


	if (strncmp((const char *)field[0], "!AIVDO", 6) != 0)
	    gpsd_report(LOG_ERROR, "invalid empty AIS channel. Assuming 'A'\n");
	ais_context = &ais_contexts[0];
	break;
    case '1':

    case 'A':
	ais_context = &ais_contexts[0];
	break;
    case '2':

    case 'B':
	ais_context = &ais_contexts[1];
	break;
    default:
	gpsd_report(LOG_ERROR, "invalid AIS channel 0x%0X .\n", field[4][0]);
	return false;
    }

    nfrags = atoi((char *)field[1]);
    ifrag = atoi((char *)field[2]);
    data = field[5];
    pad = field[6][0];
    gpsd_report(LOG_PROG, "nfrags=%d, ifrag=%d, decoded_frags=%d, data=%s\n",
		nfrags, ifrag, ais_context->decoded_frags, data);


    if (ifrag != ais_context->decoded_frags + 1) {
	gpsd_report(LOG_ERROR, "invalid fragment #%d received, expected #%d.\n",
	                       ifrag, ais_context->decoded_frags + 1);
	if (ifrag != 1)
	    return false;


        ais_context->decoded_frags = 0;
    }
    if (ifrag == 1) {
	(void)memset(ais_context->bits, '\0', sizeof(ais_context->bits));
	ais_context->bitlen = 0;
    }


    for (cp = data; cp < data + strlen((char *)data); cp++) {
	ch = *cp;
	ch -= 48;
	if (ch >= 40)
	    ch -= 8;
#ifdef __UNUSED_DEBUG__
	gpsd_report(LOG_RAW, "%c: %s\n", *cp, sixbits[ch]);
#endif

	for (i = 5; i >= 0; i--) {
	    if ((ch >> i) & 0x01) {
		ais_context->bits[ais_context->bitlen / 8] |=
		    (1 << (7 - ais_context->bitlen % 8));
	    }
	    ais_context->bitlen++;
	    if (ais_context->bitlen > sizeof(ais_context->bits)) {
		gpsd_report(LOG_INF, "overlong AIVDM payload truncated.\n");
		return false;
	    }
	}

    }
    if (isdigit(pad))
	ais_context->bitlen -= (pad - '0');


    if (ifrag == nfrags) {
	if (debug >= LOG_INF) {
	    size_t clen = (ais_context->bitlen + 7) / 8;
	    gpsd_report(LOG_INF, "AIVDM payload is %zd bits, %zd chars: %s\n",
			ais_context->bitlen, clen,
			gpsd_hexdump((char *)ais_context->bits, clen));
	}


        ais_context->decoded_frags = 0;


	return ais_binary_decode(ais,
				 ais_context->bits,
				 ais_context->bitlen,
				 &ais_context->type24_queue);
    }


    ais_context->decoded_frags++;
    return false;
}
