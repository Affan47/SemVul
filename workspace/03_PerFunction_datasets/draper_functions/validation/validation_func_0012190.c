soap_set_dime_attachment(struct soap *soap, char *ptr, size_t size, const char *type, const char *id, unsigned short optype, const char *option)
{ struct soap_multipart *content = soap_new_multipart(soap, &soap->dime.first, &soap->dime.last, ptr, size);
  if (!content)
    return SOAP_EOM;
  content->id = soap_strdup(soap, id);
  content->type = soap_strdup(soap, type);
  content->options = soap_dime_option(soap, optype, option);
  return SOAP_OK;
}
