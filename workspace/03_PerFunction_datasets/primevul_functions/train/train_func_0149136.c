int idr_get_new(struct idr *idp, void *ptr, int *id)
{
	int rv;

	rv = idr_get_new_above_int(idp, ptr, 0);


	if (rv < 0)
		return _idr_rc_to_errno(rv);
	*id = rv;
	return 0;
}
