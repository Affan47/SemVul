omapi_addr_list_dereference (omapi_addr_list_t **h,
					    const char *file, int line)
{
	if (!h)
		return DHCP_R_INVALIDARG;

	if (!*h) {
#if defined (POINTER_DEBUG)
		log_error ("%s(%d): dereference of null pointer!", file, line);
		abort ();
#else
		return DHCP_R_INVALIDARG;
#endif
	}

	if ((*h) -> refcnt <= 0) {
#if defined (POINTER_DEBUG)
		log_error ("%s(%d): dereference of pointer with zero refcnt!",
			   file, line);
#if defined (DEBUG_RC_HISTORY)
		dump_rc_history (*h);
#endif
		abort ();
#else
		*h = 0;
		return DHCP_R_INVALIDARG;
#endif
	}

	--((*h) -> refcnt);
	rc_register (file, line, h, *h, (*h) -> refcnt, 1, RC_MISC);
	if ((*h) -> refcnt <= 0 ) {
		dfree (*h, file, line);
	}
	*h = 0;
	return ISC_R_SUCCESS;
}
