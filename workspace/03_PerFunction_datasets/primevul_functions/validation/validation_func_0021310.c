CURLcode init_telnet(struct Curl_easy *data)
{
  struct TELNET *tn;

  tn = calloc(1, sizeof(struct TELNET));
  if(!tn)
    return CURLE_OUT_OF_MEMORY;

  data->req.p.telnet = tn;

  tn->telrcv_state = CURL_TS_DATA;


  CURL_SB_CLEAR(tn);


  tn->us_preferred[CURL_TELOPT_SGA] = CURL_YES;
  tn->him_preferred[CURL_TELOPT_SGA] = CURL_YES;


  tn->us_preferred[CURL_TELOPT_BINARY] = CURL_YES;
  tn->him_preferred[CURL_TELOPT_BINARY] = CURL_YES;


  tn->him_preferred[CURL_TELOPT_ECHO] = CURL_YES;


  tn->subnegotiation[CURL_TELOPT_NAWS] = CURL_YES;
  return CURLE_OK;
}
