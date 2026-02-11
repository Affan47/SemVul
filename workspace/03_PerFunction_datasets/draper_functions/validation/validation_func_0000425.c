omapi_array_free (omapi_array_t **array,
			       const char *file, int line)
{
	omapi_array_t *aptr;
	int i;

	if (!array || !*array)
		return DHCP_R_INVALIDARG;
	aptr = *array;
	for (i = 0; i < aptr -> count; i++)
		if (aptr -> data [i] && aptr -> deref)
			(*aptr -> deref) (&aptr -> data [i], file, line);
	dfree (aptr -> data, MDL);
	dfree (aptr, MDL);
	*array = (omapi_array_t *)0;
	return ISC_R_SUCCESS;
}
