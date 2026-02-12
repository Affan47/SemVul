size_t pgpLen(const uint8_t *s, size_t slen, size_t * lenp)
{
    size_t dlen = 0;
    size_t lenlen = 0;


    if (*s < 192) {
	lenlen = 1;
	dlen = *s;
    } else if (*s < 224 && slen > 2) {
	lenlen = 2;
	dlen = (((s[0]) - 192) << 8) + s[1] + 192;
    } else if (*s == 255 && slen > 5) {
	lenlen = 5;
	dlen = pgpGrab(s+1, 4);
    }

    if (slen - lenlen < dlen)
	lenlen = 0;

    if (lenlen)
	*lenp = dlen;

    return lenlen;
}
