void rec_do(struct Curl_easy *data, int option)
{
  struct TELNET *tn = data->req.p.telnet;
  switch(tn->us[option]) {
  case CURL_NO:
    if(tn->us_preferred[option] == CURL_YES) {
      tn->us[option] = CURL_YES;
      send_negotiation(data, CURL_WILL, option);
      if(tn->subnegotiation[option] == CURL_YES)

        sendsuboption(data, option);
    }
    else if(tn->subnegotiation[option] == CURL_YES) {

      tn->us[option] = CURL_YES;
      send_negotiation(data, CURL_WILL, option);
      sendsuboption(data, option);
    }
    else
      send_negotiation(data, CURL_WONT, option);
    break;

  case CURL_YES:

    break;

  case CURL_WANTNO:
    switch(tn->usq[option]) {
    case CURL_EMPTY:

      tn->us[option] = CURL_NO;
      break;
    case CURL_OPPOSITE:

      tn->us[option] = CURL_YES;
      tn->usq[option] = CURL_EMPTY;
      break;
    }
    break;

  case CURL_WANTYES:
    switch(tn->usq[option]) {
    case CURL_EMPTY:
      tn->us[option] = CURL_YES;
      if(tn->subnegotiation[option] == CURL_YES) {

        sendsuboption(data, option);
      }
      break;
    case CURL_OPPOSITE:
      tn->us[option] = CURL_WANTNO;
      tn->himq[option] = CURL_EMPTY;
      send_negotiation(data, CURL_WONT, option);
      break;
    }
    break;
  }
}
