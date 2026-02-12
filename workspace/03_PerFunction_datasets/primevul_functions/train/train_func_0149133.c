int idr_get_new_above(struct idr *idp, void *ptr, int starting_id, int *id)
{
	int rv;

	rv = idr_get_new_above_int(idp, ptr, starting_id);


	if (rv < 0)
		return _idr_rc_to_errno(rv);
	*id = rv;
	return 0;
}
