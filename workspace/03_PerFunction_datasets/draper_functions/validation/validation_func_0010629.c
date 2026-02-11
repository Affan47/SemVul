SendErrorResponse(
    const StunMessage& msg, const talk_base::SocketAddress& addr,
    int error_code, const char* error_desc) {

  StunMessage err_msg;
  err_msg.SetType(GetStunErrorResponseType(msg.type()));
  err_msg.SetTransactionID(msg.transaction_id());

  StunErrorCodeAttribute* err_code = StunAttribute::CreateErrorCode();
  err_code->SetErrorClass(error_code / 100);
  err_code->SetNumber(error_code % 100);
  err_code->SetReason(error_desc);
  err_msg.AddAttribute(err_code);

  SendResponse(err_msg, addr);
}
