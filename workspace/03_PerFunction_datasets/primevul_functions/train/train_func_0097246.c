static int data_pending(const struct Curl_easy *data)
{
  struct connectdata *conn = data->conn;

#ifdef ENABLE_QUIC
  if(conn->transport == TRNSPRT_QUIC)
    return Curl_quic_data_pending(data);
#endif

  if(conn->handler->protocol&PROTO_FAMILY_FTP)
    return Curl_ssl_data_pending(conn, SECONDARYSOCKET);


  return conn->handler->protocol&(CURLPROTO_SCP|CURLPROTO_SFTP) ||
#ifdef USE_NGHTTP2


    ((conn->handler->protocol&PROTO_FAMILY_HTTP) && conn->httpversion >= 20) ||
#endif
    Curl_ssl_data_pending(conn, FIRSTSOCKET);
}
