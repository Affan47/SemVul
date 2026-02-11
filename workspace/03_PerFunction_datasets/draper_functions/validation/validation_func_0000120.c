soap_instantiate_t__adder(struct soap *soap, int n, const char *type, const char *arrayType, size_t *size)
{
	(void)type; (void)arrayType;
	DBGLOG(TEST, SOAP_MESSAGE(fdebug, "soap_instantiate_t__adder(%d, %s, %s)\n", n, type?type:"", arrayType?arrayType:""));
	struct soap_clist *cp = soap_link(soap, NULL, SOAP_TYPE_t__adder, n, soap_fdelete);
	if (!cp)
		return NULL;
	if (type && !soap_match_tag(soap, type, "t:counter"))
	{	cp->type = SOAP_TYPE_t__counter;
		if (n < 0)
		{	cp->ptr = (void*)SOAP_NEW(t__counter);
			if (size)
				*size = sizeof(t__counter);
		}
		else
		{	cp->ptr = (void*)SOAP_NEW_ARRAY(t__counter, n);
			if (size)
				*size = n * sizeof(t__counter);
		}
		DBGLOG(TEST, SOAP_MESSAGE(fdebug, "Instantiated location=%p\n", cp->ptr));
		if (!cp->ptr)
			soap->error = SOAP_EOM;
		return (t__counter*)cp->ptr;
	}
	if (n < 0)
	{	cp->ptr = (void*)SOAP_NEW(t__adder);
		if (size)
			*size = sizeof(t__adder);
	}
	else
	{	cp->ptr = (void*)SOAP_NEW_ARRAY(t__adder, n);
		if (size)
			*size = n * sizeof(t__adder);
	}
	DBGLOG(TEST, SOAP_MESSAGE(fdebug, "Instantiated location=%p\n", cp->ptr));
	if (!cp->ptr)
		soap->error = SOAP_EOM;
	return (t__adder*)cp->ptr;
}
