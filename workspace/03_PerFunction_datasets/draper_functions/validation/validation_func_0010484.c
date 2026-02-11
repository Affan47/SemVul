putRGBseparate16bittile(
    u_long* cp,
    const u_char* r, const u_char* g, const u_char* b,
    const RGBvalue* Map,
    u_long w, u_long h,
    int fromskew, int toskew
) {
    u_long x;

    if (Map) {
	while (h-- > 0) {
	    for (x = w; x > 0; x--)
		*cp++ = PACK(Map[*r++], Map[*g++], Map[*b++]);
	    SKEW(r, g, b, fromskew);
	    cp += toskew;
	}
    } else {
	while (h-- > 0) {
	    for (x = 0; x < w; x++)
		*cp++ = PACK(*r++, *g++, *b++);
	    SKEW(r, g, b, fromskew);
	    cp += toskew;
	}
    }
}
