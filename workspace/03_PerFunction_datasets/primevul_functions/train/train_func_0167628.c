void packet_parse(struct gps_packet_t *lexer)

{
    lexer->outbuflen = 0;
    while (packet_buffered_input(lexer) > 0) {

	unsigned char c = *lexer->inbufptr++;

	char *state_table[] = {
#include "packet_names.h"
	};
	nextstate(lexer, c);
	gpsd_report(LOG_RAW + 2,
		    "%08ld: character '%c' [%02x], new state: %s\n",
		    lexer->char_counter, (isprint(c) ? c : '.'), c,
		    state_table[lexer->state]);
	lexer->char_counter++;

	if (lexer->state == GROUND_STATE) {
	    character_discard(lexer);
	} else if (lexer->state == COMMENT_RECOGNIZED) {
	    packet_accept(lexer, COMMENT_PACKET);
	    packet_discard(lexer);
	    lexer->state = GROUND_STATE;
	    break;
	}
#ifdef NMEA_ENABLE
	else if (lexer->state == NMEA_RECOGNIZED) {


	    if (strncmp((const char *)lexer->inbuffer, "$PASHR,", 7) != 0)
	    {
		bool checksum_ok = true;
		char csum[3] = { '0', '0', '0' };
		char *end;


		for (end = (char *)lexer->inbufptr - 1; isspace(*end); end--)
		    continue;
		while (strchr("0123456789ABCDEF", *end))
		    --end;
		if (*end == '*') {
		    unsigned int n, crc = 0;
		    for (n = 1; (char *)lexer->inbuffer + n < end; n++)
			crc ^= lexer->inbuffer[n];
		    (void)snprintf(csum, sizeof(csum), "%02X", crc);
		    checksum_ok = (csum[0] == toupper(end[1])
				   && csum[1] == toupper(end[2]));
		}
		if (!checksum_ok) {
		    gpsd_report(LOG_WARN,
				"bad checksum in NMEA packet; expected %s.\n",
				csum);
		    packet_accept(lexer, BAD_PACKET);
		    lexer->state = GROUND_STATE;
		    packet_discard(lexer);
		    break;
		}
	    }

#ifdef AIVDM_ENABLE
	    if (strncmp((char *)lexer->inbuffer, "!AIVDM", 6) == 0)
		packet_accept(lexer, AIVDM_PACKET);
	    else if (strncmp((char *)lexer->inbuffer, "!AIVDO", 6) == 0)
		packet_accept(lexer, AIVDM_PACKET);
	    else if (strncmp((char *)lexer->inbuffer, "!BSVDM", 6) == 0)
		packet_accept(lexer, AIVDM_PACKET);
	    else if (strncmp((char *)lexer->inbuffer, "!BSVDO", 6) == 0)
		packet_accept(lexer, AIVDM_PACKET);
	    else
#endif
		packet_accept(lexer, NMEA_PACKET);
	    packet_discard(lexer);
	    break;
	}
#endif
#ifdef SIRF_ENABLE
	else if (lexer->state == SIRF_RECOGNIZED) {
	    unsigned char *trailer = lexer->inbufptr - 4;
	    unsigned int checksum =
		(unsigned)((trailer[0] << 8) | trailer[1]);
	    unsigned int n, crc = 0;
	    for (n = 4; n < (unsigned)(trailer - lexer->inbuffer); n++)
		crc += (int)lexer->inbuffer[n];
	    crc &= 0x7fff;
	    if (checksum == crc)
		packet_accept(lexer, SIRF_PACKET);
	    else {
		packet_accept(lexer, BAD_PACKET);
		lexer->state = GROUND_STATE;
	    }
	    packet_discard(lexer);
	    break;
	}
#endif
#ifdef SUPERSTAR2_ENABLE
	else if (lexer->state == SUPERSTAR2_RECOGNIZED) {
	    unsigned a = 0, b;
	    size_t n;
	    lexer->length = 4 + (size_t) lexer->inbuffer[3] + 2;
	    for (n = 0; n < lexer->length - 2; n++)
		a += (unsigned)lexer->inbuffer[n];
	    b = (unsigned)getleu16(lexer->inbuffer, lexer->length - 2);
	    gpsd_report(LOG_IO, "SuperStarII pkt dump: type %u len %u\n",
			lexer->inbuffer[1], (unsigned int)lexer->length);
	    if (a != b) {
		gpsd_report(LOG_IO, "REJECT SuperStarII packet type 0x%02x"
			    "%zd bad checksum 0x%04x, expecting 0x%04x\n",
			    lexer->inbuffer[1], lexer->length, a, b);
		packet_accept(lexer, BAD_PACKET);
		lexer->state = GROUND_STATE;
	    } else {
		packet_accept(lexer, SUPERSTAR2_PACKET);
	    }
	    packet_discard(lexer);
	    break;
	}
#endif
#ifdef ONCORE_ENABLE
	else if (lexer->state == ONCORE_RECOGNIZED) {
	    char a, b;
	    int i, len;

	    len = lexer->inbufptr - lexer->inbuffer;
	    a = (char)(lexer->inbuffer[len - 3]);
	    b = '\0';
	    for (i = 2; i < len - 3; i++)
		b ^= lexer->inbuffer[i];
	    if (a == b) {
		gpsd_report(LOG_IO, "Accept OnCore packet @@%c%c len %d\n",
			    lexer->inbuffer[2], lexer->inbuffer[3], len);
		packet_accept(lexer, ONCORE_PACKET);
	    } else {
		gpsd_report(LOG_IO, "REJECT OnCore packet @@%c%c len %d\n",
			    lexer->inbuffer[2], lexer->inbuffer[3], len);
		packet_accept(lexer, BAD_PACKET);
		lexer->state = GROUND_STATE;
	    }
	    packet_discard(lexer);
	    break;
	}
#endif
#if defined(TSIP_ENABLE) || defined(GARMIN_ENABLE)
	else if (lexer->state == TSIP_RECOGNIZED) {
	    size_t packetlen = lexer->inbufptr - lexer->inbuffer;
#ifdef TSIP_ENABLE
	    unsigned int pos, dlecnt;

	    dlecnt = 0;
	    for (pos = 0; pos < (unsigned int)packetlen; pos++)
		if (lexer->inbuffer[pos] == DLE)
		    dlecnt++;
	    if (dlecnt > 2) {
		dlecnt -= 2;
		dlecnt /= 2;
		gpsd_report(LOG_RAW, "Unstuffed %d DLEs\n", dlecnt);
		packetlen -= dlecnt;
	    }
#endif
	    if (packetlen < 5) {
		lexer->state = GROUND_STATE;
	    } else {
		unsigned int pkt_id;
#ifdef GARMIN_ENABLE
		unsigned int len;
		size_t n;
		unsigned int ch, chksum;
		n = 0;

#ifdef TSIP_ENABLE

		if (TSIP_PACKET == lexer->type)
		    goto not_garmin;
#endif
		if (lexer->inbuffer[n++] != DLE)
		    goto not_garmin;
		pkt_id = lexer->inbuffer[n++];
		len = lexer->inbuffer[n++];
		chksum = len + pkt_id;
		if (len == DLE) {
		    if (lexer->inbuffer[n++] != DLE)
			goto not_garmin;
		}
		for (; len > 0; len--) {
		    chksum += lexer->inbuffer[n];
		    if (lexer->inbuffer[n++] == DLE) {
			if (lexer->inbuffer[n++] != DLE)
			    goto not_garmin;
		    }
		}

		ch = lexer->inbuffer[n++];
		chksum += ch;
		if (ch == DLE) {
		    if (lexer->inbuffer[n++] != DLE)
			goto not_garmin;
		}
		if (lexer->inbuffer[n++] != DLE)
		    goto not_garmin;

		if (lexer->inbuffer[n] != ETX)
		    goto not_garmin;

		chksum &= 0xff;
		if (chksum) {
		    gpsd_report(LOG_IO,
				"Garmin checksum failed: %02x!=0\n", chksum);
		    goto not_garmin;
		}
		packet_accept(lexer, GARMIN_PACKET);
		packet_discard(lexer);
		break;
	      not_garmin:;
		gpsd_report(LOG_RAW + 1, "Not a Garmin packet\n");
#endif
#ifdef TSIP_ENABLE


		pkt_id = lexer->inbuffer[1];

		if (!((0x13 == pkt_id) || (0xbb == pkt_id) || (0xbc == pkt_id)  || (0x38 == pkt_id))
		    && ((0x41 > pkt_id) || (0x8f < pkt_id))) {
		    gpsd_report(LOG_IO,
				"Packet ID 0x%02x out of range for TSIP\n",
				pkt_id);
		    goto not_tsip;
		}


		if ((0x13 == pkt_id) && (0x01 <= packetlen))
		     ;
		else if ((0x38 == pkt_id) && (0x03 == packetlen))
		     ;
		else if ((0x41 == pkt_id)
			 && ((0x0e == packetlen) || (0x0f == packetlen)))
		     ;
		else if ((0x42 == pkt_id) && (0x14 == packetlen))
		     ;
		else if ((0x43 == pkt_id) && (0x18 == packetlen))
		     ;
		else if ((0x45 == pkt_id) && (0x0e == packetlen))
		     ;
		else if ((0x46 == pkt_id) && (0x06 == packetlen))
		     ;
		else if ((0x48 == pkt_id) && (0x1a == packetlen))
		     ;
		else if ((0x49 == pkt_id) && (0x24 == packetlen))
		     ;
		else if ((0x4a == pkt_id) && (0x18 == packetlen))
		     ;
		else if ((0x4b == pkt_id) && (0x07 == packetlen))
		     ;
		else if ((0x4c == pkt_id) && (0x15 == packetlen))
		     ;
		else if ((0x54 == pkt_id) && (0x10 == packetlen))
		     ;
		else if ((0x55 == pkt_id) && (0x08 == packetlen))
		     ;
		else if ((0x56 == pkt_id) && (0x18 == packetlen))
		     ;
		else if ((0x57 == pkt_id) && (0x0c == packetlen))
		     ;
		else if ((0x5a == pkt_id)
			 && ((0x1d <= packetlen) && (0x1f >= packetlen)))
		     ;
		else if ((0x5b == pkt_id) && (0x24 == packetlen))
		     ;
		else if ((0x5c == pkt_id)
			 && ((0x1c <= packetlen) && (0x1e >= packetlen)))
		     ;
		else if ((0x5e == pkt_id) && (0x06 == packetlen))
		     ;
		else if ((0x5f == pkt_id) && (70 == packetlen))
		     ;
		else if ((0x6d == pkt_id)
			 && ((0x14 <= packetlen) && (0x20 >= packetlen)))
		     ;
		else if ((0x82 == pkt_id) && (0x05 == packetlen))
		     ;
		else if ((0x84 == pkt_id)
			 && ((0x28 <= packetlen) && (0x29 >= packetlen)))
		     ;
		else if ((0x8e == pkt_id))
		     ;
		else if ((0x8f == pkt_id))
		     ;
		else if ((0xbb == pkt_id) && (0x2c == packetlen))
		     ;
		else {
		    gpsd_report(LOG_IO,
				"TSIP REJECT pkt_id = %#02x, packetlen= %zu\n",
				pkt_id, packetlen);
		    goto not_tsip;
		}

		gpsd_report(LOG_RAW,
			    "TSIP pkt_id = %#02x, packetlen= %zu\n",
			    pkt_id, packetlen);

		packet_accept(lexer, TSIP_PACKET);
		packet_discard(lexer);
		break;
	      not_tsip:
		gpsd_report(LOG_RAW + 1, "Not a TSIP packet\n");


		packet_accept(lexer, BAD_PACKET);
		lexer->state = GROUND_STATE;
		packet_discard(lexer);
		break;
#endif
	    }
	}
#endif
#ifdef RTCM104V3_ENABLE
	else if (lexer->state == RTCM3_RECOGNIZED) {
	    if (crc24q_check(lexer->inbuffer,
			     lexer->inbufptr - lexer->inbuffer)) {
		packet_accept(lexer, RTCM3_PACKET);
	    } else {
		gpsd_report(LOG_IO, "RTCM3 data checksum failure, "
			    "%0x against %02x %02x %02x\n",
			    crc24q_hash(lexer->inbuffer,
					lexer->inbufptr - lexer->inbuffer -
					3), lexer->inbufptr[-3],
			    lexer->inbufptr[-2], lexer->inbufptr[-1]);
		packet_accept(lexer, BAD_PACKET);
	    }
	    packet_discard(lexer);
	    lexer->state = GROUND_STATE;
	    break;
	}
#endif
#ifdef ZODIAC_ENABLE
	else if (lexer->state == ZODIAC_RECOGNIZED) {
	    short len, n, sum;
	    len = getword(2);
	    for (n = sum = 0; n < len; n++)
		sum += getword(5 + n);
	    sum *= -1;
	    if (len == 0 || sum == getword(5 + len)) {
		packet_accept(lexer, ZODIAC_PACKET);
	    } else {
		gpsd_report(LOG_IO,
			    "Zodiac data checksum 0x%hx over length %hd, expecting 0x%hx\n",
			    sum, len, getword(5 + len));
		packet_accept(lexer, BAD_PACKET);
		lexer->state = GROUND_STATE;
	    }
	    packet_discard(lexer);
	    break;
	}
#endif
#ifdef UBX_ENABLE
	else if (lexer->state == UBX_RECOGNIZED) {

	    int n, len;
	    unsigned char ck_a = (unsigned char)0;
	    unsigned char ck_b = (unsigned char)0;
	    len = lexer->inbufptr - lexer->inbuffer;
	    gpsd_report(LOG_IO, "UBX: len %d\n", len);
	    for (n = 2; n < (len - 2); n++) {
		ck_a += lexer->inbuffer[n];
		ck_b += ck_a;
	    }
	    if (ck_a == lexer->inbuffer[len - 2] &&
		ck_b == lexer->inbuffer[len - 1])
		packet_accept(lexer, UBX_PACKET);
	    else {
		gpsd_report(LOG_IO,
			    "UBX checksum 0x%02hhx%02hhx over length %d,"
			    " expecting 0x%02hhx%02hhx (type 0x%02hhx%02hhx)\n",
			    ck_a,
			    ck_b,
			    len,
			    lexer->inbuffer[len - 2],
			    lexer->inbuffer[len - 1],
			    lexer->inbuffer[2], lexer->inbuffer[3]);
		packet_accept(lexer, BAD_PACKET);
		lexer->state = GROUND_STATE;
	    }
	    packet_discard(lexer);
	    break;
	}
#endif
#ifdef EVERMORE_ENABLE
	else if (lexer->state == EVERMORE_RECOGNIZED) {
	    unsigned int n, crc, checksum, len;
	    n = 0;

	    if (lexer->inbuffer[n++] != DLE)
		goto not_evermore;
	    if (lexer->inbuffer[n++] != STX)
		goto not_evermore;
	    len = lexer->inbuffer[n++];
	    if (len == DLE) {
		if (lexer->inbuffer[n++] != DLE)
		    goto not_evermore;
	    }
	    len -= 2;
	    crc = 0;
	    for (; len > 0; len--) {
		crc += lexer->inbuffer[n];
		if (lexer->inbuffer[n++] == DLE) {
		    if (lexer->inbuffer[n++] != DLE)
			goto not_evermore;
		}
	    }
	    checksum = lexer->inbuffer[n++];
	    if (checksum == DLE) {
		if (lexer->inbuffer[n++] != DLE)
		    goto not_evermore;
	    }
	    if (lexer->inbuffer[n++] != DLE)
		goto not_evermore;

	    if (lexer->inbuffer[n] != ETX)
		goto not_evermore;
	    crc &= 0xff;
	    if (crc != checksum) {
		gpsd_report(LOG_IO,
			    "EverMore checksum failed: %02x != %02x\n",
			    crc, checksum);
		goto not_evermore;
	    }

	    packet_accept(lexer, EVERMORE_PACKET);
	    packet_discard(lexer);
	    break;
	  not_evermore:
	    packet_accept(lexer, BAD_PACKET);
	    lexer->state = GROUND_STATE;
	    packet_discard(lexer);
	    break;
	}
#endif

#ifdef ITRAX_ENABLE
#define getib(j) ((uint8_t)lexer->inbuffer[(j)])
#define getiw(i) ((uint16_t)(((uint16_t)getib((i)+1) << 8) | (uint16_t)getib((i))))

	else if (lexer->state == ITALK_RECOGNIZED) {
	    volatile uint16_t len, n, csum, xsum;


	    len = (uint16_t) (lexer->inbuffer[6] & 0xff);


	    xsum = getiw(7 + 2 * len);


	    csum = 0;
	    for (n = 0; n < len; n++) {
		volatile uint16_t tmpw = getiw(7 + 2 * n);
		volatile uint32_t tmpdw  = (csum + 1) * (tmpw + n);
		csum ^= (tmpdw & 0xffff) ^ ((tmpdw >> 16) & 0xffff);
	    }

	    if (len == 0 || csum == xsum)
		packet_accept(lexer, ITALK_PACKET);
	    else {
		gpsd_report(LOG_IO,
			    "ITALK: checksum failed - "
			    "type 0x%02x expected 0x%04x got 0x%04x\n",
			    lexer->inbuffer[4], xsum, csum);
		packet_accept(lexer, BAD_PACKET);
		lexer->state = GROUND_STATE;
	    }
	    packet_discard(lexer);
	    break;
	}
#undef getiw
#undef getib
#endif
#ifdef NAVCOM_ENABLE
	else if (lexer->state == NAVCOM_RECOGNIZED) {

	    packet_accept(lexer, NAVCOM_PACKET);
	    packet_discard(lexer);
	    break;
	}
#endif
#ifdef GEOSTAR_ENABLE
	else if (lexer->state == GEOSTAR_RECOGNIZED) {

	    int n, len;
	    unsigned int cs = 0L;
	    len = lexer->inbufptr - lexer->inbuffer;


	    for (n = 0; n < len; n += 4) {
		cs ^= getleu32(lexer->inbuffer, n);
	    }

	    if (cs == 0)
		packet_accept(lexer, GEOSTAR_PACKET);
	    else {
		gpsd_report(LOG_IO,
			    "GeoStar checksum failed 0x%x over length %d\n",
			    cs, len);
		packet_accept(lexer, BAD_PACKET);
		lexer->state = GROUND_STATE;
	    }
	    packet_discard(lexer);
	    break;
	}
#endif
#ifdef RTCM104V2_ENABLE
	else if (lexer->state == RTCM2_RECOGNIZED) {


	    packet_accept(lexer, RTCM2_PACKET);
	    lexer->state = RTCM2_SYNC_STATE;
	    packet_discard(lexer);
	    break;
	}
#endif
#ifdef GARMINTXT_ENABLE
	else if (lexer->state == GTXT_RECOGNIZED) {
	    size_t packetlen = lexer->inbufptr - lexer->inbuffer;
	    if (57 <= packetlen) {
		packet_accept(lexer, GARMINTXT_PACKET);
		packet_discard(lexer);
		lexer->state = GROUND_STATE;
		break;
	    } else {
		packet_accept(lexer, BAD_PACKET);
		lexer->state = GROUND_STATE;
	    }
	}
#endif
#ifdef PASSTHROUGH_ENABLE
	else if (lexer->state == JSON_RECOGNIZED) {
	    size_t packetlen = lexer->inbufptr - lexer->inbuffer;
	    if (packetlen >= 11)

		packet_accept(lexer, JSON_PACKET);
	    else
		packet_accept(lexer, BAD_PACKET);
	    packet_discard(lexer);
	    lexer->state = GROUND_STATE;
	    break;
	}
#endif
    }
}
