static int decodePkt(const uint8_t *p, size_t plen, struct pgpPkt *pkt)
{
    int rc = -1;


    if (p && plen >= 2 && p[0] & 0x80) {
	size_t lenlen = 0;
	size_t hlen = 0;

	if (p[0] & 0x40) {

	    lenlen = pgpLen(p+1, plen-1, &pkt->blen);
	    pkt->tag = (p[0] & 0x3f);
	} else {

	    lenlen = (1 << (p[0] & 0x3));
	    if (plen > lenlen) {
		pkt->blen = pgpGrab(p+1, lenlen);
	    }
	    pkt->tag = (p[0] >> 2) & 0xf;
	}
	hlen = lenlen + 1;


	if (lenlen && (hlen + pkt->blen <= plen)) {
	    pkt->head = p;
	    pkt->body = pkt->head + hlen;
	    rc = 0;
	}
    }

    return rc;
}
