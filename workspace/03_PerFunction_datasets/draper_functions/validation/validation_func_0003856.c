simpleprng_verify_buffer(
    simpleprng_state_t *state,
    gpointer buf,
    size_t len)
{
    guint8 *p = buf;
    while (len--) {
	guint64 count = state->count;
	guint8 expected = simpleprng_rand_byte(state);
	guint8 got = *p;
	if (expected != got) {
	    int remaining = MIN(len, 16);
	    guint8 expbytes[16] = { expected };
	    char *gotstr = hexstr(p, remaining);
	    char *expstr;
	    int i;

	    for (i = 1; i < remaining; i++)
		expbytes[i] = simpleprng_rand_byte(state);
	    expstr = hexstr(expbytes, remaining);

	    g_fprintf(stderr,
		    "random value mismatch at offset %ju: got %s, expected %s\n",
		    (uintmax_t)count, gotstr, expstr);
	    g_free(gotstr);
	    return FALSE;
	}
	p++;
    }

    return TRUE;
}
