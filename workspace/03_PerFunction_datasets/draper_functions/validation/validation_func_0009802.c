__log_inmem_copyout(dblp, offset, buf, size)
	DB_LOG *dblp;
	size_t offset;
	void *buf;
	size_t size;
{
	LOG *lp;
	size_t nbytes;

	lp = (LOG *)dblp->reginfo.primary;
	nbytes = (offset + size < lp->buffer_size) ?
	    size : lp->buffer_size - offset;
	memcpy(buf, dblp->bufp + offset, nbytes);
	if (nbytes < size)
		memcpy((u_int8_t *)buf + nbytes, dblp->bufp, size - nbytes);
}
