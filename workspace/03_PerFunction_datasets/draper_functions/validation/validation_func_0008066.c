soap_copy_fault(struct soap *soap, const char *faultcode, const char *faultsubcodeQName, const char *faultstring, const char *faultdetailXML)
{ char *r = NULL, *s = NULL, *t = NULL;
  if (faultsubcodeQName)
    r = soap_strdup(soap, faultsubcodeQName);
  if (faultstring)
    s = soap_strdup(soap, faultstring);
  if (faultdetailXML)
    t = soap_strdup(soap, faultdetailXML);
  return soap_set_error(soap, faultcode, r, s, t, SOAP_FAULT);
}
