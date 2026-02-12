HTTP_estimate(unsigned nhttp)
{


	return (PRNDUP(sizeof(struct http) + sizeof(txt) * nhttp + nhttp));
}
