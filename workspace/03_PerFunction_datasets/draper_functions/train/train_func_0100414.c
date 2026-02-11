soap_double2s(struct soap *soap, double n)
{ char *s;
  if (soap_isnan(n))
    return "NaN";
  if (soap_ispinfd(n))
    return "INF";
  if (soap_isninfd(n))
    return "-INF";
  s = soap->tmpbuf;
#if defined(HAVE_SPRINTF_L)
  sprintf_l(s, soap->c_locale, soap->double_format, n);
#else
  sprintf(s, soap->double_format, n);
  s = strchr(s, ',');
  if (s)
    *s = '.';
#endif
  return soap->tmpbuf;
}
