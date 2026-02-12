CURLcode Curl_connect(struct Curl_easy *data,
                      struct connectdata **in_connect,
                      bool *asyncp,
                      bool *protocol_done)
{
  CURLcode result;

  *asyncp = FALSE;


  result = create_conn(data, in_connect, asyncp);

  if(!result) {

    if((*in_connect)->send_pipe.size || (*in_connect)->recv_pipe.size)

      *protocol_done = TRUE;
    else if(!*asyncp) {


      result = Curl_setup_conn(*in_connect, protocol_done);
    }
  }

  if(result == CURLE_NO_CONNECTION_AVAILABLE) {
    *in_connect = NULL;
    return result;
  }

  if(result && *in_connect) {


    Curl_disconnect(*in_connect, FALSE);
    *in_connect = NULL;
  }

  return result;
}
