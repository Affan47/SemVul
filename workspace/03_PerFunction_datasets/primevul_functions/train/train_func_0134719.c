static CURLcode imap_state_fetch_resp(struct connectdata *conn, int imapcode,
                                      imapstate instate)
{
  CURLcode result = CURLE_OK;
  struct Curl_easy *data = conn->data;
  struct imap_conn *imapc = &conn->proto.imapc;
  struct pingpong *pp = &imapc->pp;
  const char *ptr = data->state.buffer;
  bool parsed = FALSE;
  curl_off_t size = 0;

  (void)instate;

  if(imapcode != '*') {
    Curl_pgrsSetDownloadSize(data, -1);
    state(conn, IMAP_STOP);
    return CURLE_REMOTE_FILE_NOT_FOUND;
  }

  while(*ptr && (*ptr != '{'))
    ptr++;

  if(*ptr == '{') {
    char *endptr;
    if(!curlx_strtoofft(ptr + 1, &endptr, 10, &size)) {
      if(endptr - ptr > 1 && endptr[0] == '}' &&
         endptr[1] == '\r' && endptr[2] == '\0')
        parsed = TRUE;
    }
  }

  if(parsed) {
    infof(data, "Found %" CURL_FORMAT_CURL_OFF_TU " bytes to download\n",
          size);
    Curl_pgrsSetDownloadSize(data, size);

    if(pp->cache) {

      size_t chunk = pp->cache_size;

      if(chunk > (size_t)size)

        chunk = (size_t)size;

      if(!chunk) {

        state(conn, IMAP_STOP);
        return CURLE_OK;
      }
      result = Curl_client_write(conn, CLIENTWRITE_BODY, pp->cache, chunk);
      if(result)
        return result;

      data->req.bytecount += chunk;

      infof(data, "Written %" CURL_FORMAT_CURL_OFF_TU
            " bytes, %" CURL_FORMAT_CURL_OFF_TU
            " bytes are left for transfer\n", (curl_off_t)chunk,
            size - chunk);

      if(pp->cache_size > chunk) {

        memmove(pp->cache, pp->cache + chunk, pp->cache_size - chunk);
        pp->cache_size -= chunk;
      }
      else {

        Curl_safefree(pp->cache);

        pp->cache_size = 0;
      }
    }

    if(data->req.bytecount == size)

      Curl_setup_transfer(conn, -1, -1, FALSE, NULL, -1, NULL);
    else {

      data->req.maxdownload = size;
      Curl_setup_transfer(conn, FIRSTSOCKET, size, FALSE, NULL, -1, NULL);
    }
  }
  else {

    failf(pp->conn->data, "Failed to parse FETCH response.");
    result = CURLE_WEIRD_SERVER_REPLY;
  }

  state(conn, IMAP_STOP);

  return result;
}
}
