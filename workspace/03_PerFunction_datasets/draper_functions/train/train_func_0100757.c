dico_stream_readln(dico_stream_t stream, char *buf, size_t size, size_t *pread)
{
    int rc;
    char c;
    size_t n = 0;

    if (size == 0)
	return EIO;

    size--;
    for (n = 0; n < size && (rc = dico_stream_read(stream, &c, 1, NULL)) == 0;
	 n++) {
	*buf++ = c;
	if (c == '\n')
	    break;
    }
    *buf = 0;
    if (pread)
	*pread = n;
    return rc;
}
