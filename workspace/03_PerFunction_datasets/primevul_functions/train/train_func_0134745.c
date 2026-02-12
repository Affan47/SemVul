static CURLcode imap_sendf(struct connectdata *conn, const char *fmt, ...)
{
  CURLcode result = CURLE_OK;
  struct imap_conn *imapc = &conn->proto.imapc;
  char *taggedfmt;
  va_list ap;

  DEBUGASSERT(fmt);


  imapc->cmdid = (imapc->cmdid + 1) % 1000;


  snprintf(imapc->resptag, sizeof(imapc->resptag), "%c%03d",
           'A' + curlx_sltosi(conn->connection_id % 26), imapc->cmdid);


  taggedfmt = aprintf("%s %s", imapc->resptag, fmt);
  if(!taggedfmt)
    return CURLE_OUT_OF_MEMORY;


  va_start(ap, fmt);
  result = Curl_pp_vsendf(&imapc->pp, taggedfmt, ap);
  va_end(ap);

  free(taggedfmt);

  return result;
}
