static CURLcode imap_state_auth_resp(struct connectdata *conn,
                                     int imapcode,
                                     imapstate instate)
{
  CURLcode result = CURLE_OK;
  struct Curl_easy *data = conn->data;
  struct imap_conn *imapc = &conn->proto.imapc;
  saslprogress progress;

  (void)instate;

  result = Curl_sasl_continue(&imapc->sasl, conn, imapcode, &progress);
  if(!result)
    switch(progress) {
    case SASL_DONE:
      state(conn, IMAP_STOP);
      break;
    case SASL_IDLE:
      if((!imapc->login_disabled) && (imapc->preftype & IMAP_TYPE_CLEARTEXT))

        result = imap_perform_login(conn);
      else {
        failf(data, "Authentication cancelled");
        result = CURLE_LOGIN_DENIED;
      }
      break;
    default:
      break;
    }

  return result;
}
