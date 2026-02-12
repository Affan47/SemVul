void ProtocolV1::reset_security()
{
  ldout(cct, 5) << __func__ << dendl;


  if (state == CONNECTING_SEND_CONNECT_MSG) {
    if (authorizer) {
      delete authorizer;
    }
    authorizer = nullptr;
  }
}
