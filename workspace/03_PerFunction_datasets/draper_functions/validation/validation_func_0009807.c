soap_inwliteral(struct soap *soap, const char *tag, wchar_t **p)
{ if (soap_element_begin_in(soap, tag, 1, NULL))
  { if (soap->error != SOAP_NO_TAG || soap_unget(soap, soap_get(soap)) == SOAP_TT)
      return NULL;
    soap->error = SOAP_OK;
  }
  if (!p)
  { if (!(p = (wchar_t**)soap_malloc(soap, sizeof(wchar_t*))))
      return NULL;
  }
  if (soap->body)
  { *p = soap_wstring_in(soap, 0, -1, -1);
    if (!*p)
      return NULL;
    if (!**p && tag && *tag == '-')
    { soap->error = SOAP_NO_TAG;
      return NULL;
    }
  }
  else if (tag && *tag == '-')
  { soap->error = SOAP_NO_TAG;
    return NULL;
  }
  else if (soap->null)
    *p = NULL;
  else
    *p = soap_wstrdup(soap, (wchar_t*)SOAP_STR_EOS);
  if (soap->body && soap_element_end_in(soap, tag))
    return NULL;
  return p;
}
