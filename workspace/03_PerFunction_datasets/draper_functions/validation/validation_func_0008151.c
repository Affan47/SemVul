OnDataReceived(cricket::Call*,
                                const cricket::ReceiveDataParams& params,
                                const std::string& data) {
  cricket::StreamParams stream;
  if (GetStreamBySsrc(call_->data_recv_streams(), params.ssrc, &stream)) {
    console_->PrintLine(
        "Received data from '%s' on stream '%s' (ssrc=%u): %s",
        stream.nick.c_str(), stream.name.c_str(),
        params.ssrc, data.c_str());
  } else {
    console_->PrintLine(
        "Received data (ssrc=%u): %s",
        params.ssrc, data.c_str());
  }
}
