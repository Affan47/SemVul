zxid_curl_read_data(void *buffer, size_t size, size_t nmemb, void *userp)
{
  int len = size*nmemb;
  struct zxid_curl_ctx* wc = (struct zxid_curl_ctx*)userp;
  if (len > (wc->lim - wc->p))
    len = wc->lim - wc->p;
  memcpy(buffer, wc->p, len);
  wc->p += len;
  if (zx_debug & CURL_INOUT) {
    INFO("SEND(%.*s) %d chars", len, (char*)buffer, len);
    D_XML_BLOB(0, "SEND", len, (char*)buffer);
  }
  return len;
}
