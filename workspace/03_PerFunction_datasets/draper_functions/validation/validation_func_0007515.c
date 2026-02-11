soap_faultdetail(struct soap *soap)
{
	soap_fault(soap);
	if (soap->version == 2)
	{	if (soap->fault->SOAP_ENV__Detail == NULL)
		{	soap->fault->SOAP_ENV__Detail = (struct SOAP_ENV__Detail*)soap_malloc(soap, sizeof(struct SOAP_ENV__Detail));
			soap_default_SOAP_ENV__Detail(soap, soap->fault->SOAP_ENV__Detail);
		}
		return (const char**)&soap->fault->SOAP_ENV__Detail->__any;
	}
	if (soap->fault->detail == NULL)
	{	soap->fault->detail = (struct SOAP_ENV__Detail*)soap_malloc(soap, sizeof(struct SOAP_ENV__Detail));
		soap_default_SOAP_ENV__Detail(soap, soap->fault->detail);
	}
	return (const char**)&soap->fault->detail->__any;
}
