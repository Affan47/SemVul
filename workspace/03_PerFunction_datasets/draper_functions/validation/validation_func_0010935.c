c_real(COMPLEX *c)
{
	COMPLEX *r;

	if (cisreal(c))
		return clink(c);
	r = comalloc();
	if (!qiszero(c->real)) {
		qfree(r->real);
		r->real = qlink(c->real);
	}
	return r;
}
