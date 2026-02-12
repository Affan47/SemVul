rb_memsearch_qs_utf8(const unsigned char *xs, long m, const unsigned char *ys, long n)
{
    const unsigned char *x = xs, *xe = xs + m;
    const unsigned char *y = ys;
    VALUE i, qstable[512];


    for (i = 0; i < 512; ++i) {
	qstable[i] = m + 1;
    }
    for (; x < xe; ++x) {
	qstable[rb_memsearch_qs_utf8_hash(x)] = xe - x;
    }

    for (; y + m <= ys + n; y += qstable[rb_memsearch_qs_utf8_hash(y+m)]) {
	if (*xs == *y && memcmp(xs, y, m) == 0)
	    return y - ys;
    }
    return -1;
}
