XML_SetEncoding(XML_Parser parser, const XML_Char *encodingName)
{
  if (parser == NULL)
      return XML_STATUS_ERROR;


  if (ps_parsing == XML_PARSING || ps_parsing == XML_SUSPENDED)
    return XML_STATUS_ERROR;
  if (encodingName == NULL)
    protocolEncodingName = NULL;
  else {
    protocolEncodingName = poolCopyString(&tempPool, encodingName);
    if (!protocolEncodingName)
      return XML_STATUS_ERROR;
  }
  return XML_STATUS_OK;
}
