static bool imap_endofresp(struct connectdata *conn, char *line, size_t len,
                           int *resp)
{
  struct IMAP *imap = conn->data->req.protop;
  struct imap_conn *imapc = &conn->proto.imapc;
  const char *id = imapc->resptag;
  size_t id_len = strlen(id);


  if(len >= id_len + 1 && !memcmp(id, line, id_len) && line[id_len] == ' ') {
    line += id_len + 1;
    len -= id_len + 1;

    if(len >= 2 && !memcmp(line, "OK", 2))
      *resp = IMAP_RESP_OK;
    else if(len >= 7 && !memcmp(line, "PREAUTH", 7))
      *resp = IMAP_RESP_PREAUTH;
    else
      *resp = IMAP_RESP_NOT_OK;

    return TRUE;
  }


  if(len >= 2 && !memcmp("* ", line, 2)) {
    switch(imapc->state) {

      case IMAP_CAPABILITY:
        if(!imap_matchresp(line, len, "CAPABILITY"))
          return FALSE;
        break;

      case IMAP_LIST:
        if((!imap->custom && !imap_matchresp(line, len, "LIST")) ||
          (imap->custom && !imap_matchresp(line, len, imap->custom) &&
           (strcmp(imap->custom, "STORE") ||
            !imap_matchresp(line, len, "FETCH")) &&
           strcmp(imap->custom, "SELECT") &&
           strcmp(imap->custom, "EXAMINE") &&
           strcmp(imap->custom, "SEARCH") &&
           strcmp(imap->custom, "EXPUNGE") &&
           strcmp(imap->custom, "LSUB") &&
           strcmp(imap->custom, "UID") &&
           strcmp(imap->custom, "NOOP")))
          return FALSE;
        break;

      case IMAP_SELECT:


        break;

      case IMAP_FETCH:
        if(!imap_matchresp(line, len, "FETCH"))
          return FALSE;
        break;

      case IMAP_SEARCH:
        if(!imap_matchresp(line, len, "SEARCH"))
          return FALSE;
        break;


      default:
        return FALSE;
    }

    *resp = '*';
    return TRUE;
  }


  if(imap && !imap->custom && ((len == 3 && !memcmp("+", line, 1)) ||
     (len >= 2 && !memcmp("+ ", line, 2)))) {
    switch(imapc->state) {

      case IMAP_AUTHENTICATE:
      case IMAP_APPEND:
        *resp = '+';
        break;

      default:
        failf(conn->data, "Unexpected continuation response");
        *resp = -1;
        break;
    }

    return TRUE;
  }

  return FALSE;
}
