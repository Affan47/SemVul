cbuf_writeptr(circbuffer *cbuf, unsigned int len) {

	if (len > cbuf_writelen(cbuf)) {
		dropbear_exit("bad cbuf write");
	}

	return &cbuf->data[cbuf->writepos];
}
