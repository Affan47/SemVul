bstr_dup(bstr_t bstr)
{

  size_t fromlen;
  bstr_t ret;

  fromlen = bstr_len(bstr);
  ret = _bstr_malloc(fromlen);
  if (ret == NULL) return NULL;

  memcpy(ret, bstr, fromlen);
  return ret;
}
