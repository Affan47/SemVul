stream_add_raw_bytes_to_binary(Stream *s, const char *buffer, int buflen)
{
    int i;

    for (i = 0; i < buflen; i++) {
	unsigned char c = buffer[i];

	if (c != '~' && (isgraph(c) || c == ' '))
	    stream_add_char(s, c);
	else
	    stream_printf(s, "~%02x", (int) c);
    }
}
