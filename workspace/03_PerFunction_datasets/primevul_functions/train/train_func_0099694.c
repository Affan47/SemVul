static CURLcode tftp_setup_connection(struct connectdata * conn)
{
  struct Curl_easy *data = conn->data;
  char *type;

  conn->transport = TRNSPRT_UDP;


  type = strstr(data->state.up.path, ";mode=");

  if(!type)
    type = strstr(conn->host.rawalloc, ";mode=");

  if(type) {
    char command;
    *type = 0;
    command = Curl_raw_toupper(type[6]);

    switch(command) {
    case 'A':
    case 'N':
      data->set.prefer_ascii = TRUE;
      break;

    case 'O':
    case 'I':
    default:

      data->set.prefer_ascii = FALSE;
      break;
    }
  }

  return CURLE_OK;
}
