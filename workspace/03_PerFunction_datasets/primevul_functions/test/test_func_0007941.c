Proto_SanityCheckRequest(ProtoRequest *request)
{


#if VGAUTH_PROTO_TRACE
   ASSERT(strncmp(request->rawData, VGAUTH_XML_PREAMBLE,
                  strlen(VGAUTH_XML_PREAMBLE)) == 0);
#endif
   return VGAUTH_E_OK;
}
