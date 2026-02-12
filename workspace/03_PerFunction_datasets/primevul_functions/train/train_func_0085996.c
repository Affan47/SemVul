ErrorCode HTTP2Codec::handleEndStream() {
  if (curHeader_.type != http2::FrameType::HEADERS &&
      curHeader_.type != http2::FrameType::EX_HEADERS &&
      curHeader_.type != http2::FrameType::CONTINUATION &&
      curHeader_.type != http2::FrameType::DATA) {
    return ErrorCode::NO_ERROR;
  }


  pendingEndStreamHandling_ |= (curHeader_.flags & http2::END_STREAM);


  if (ingressWebsocketUpgrade_) {
    ingressWebsocketUpgrade_ = false;
    deliverCallbackIfAllowed(&HTTPCodec::Callback::onMessageComplete,
                             "onMessageComplete", curHeader_.stream, true);
  }

  if (pendingEndStreamHandling_ && expectedContinuationStream_ == 0) {
    pendingEndStreamHandling_ = false;
    deliverCallbackIfAllowed(&HTTPCodec::Callback::onMessageComplete,
                             "onMessageComplete", curHeader_.stream, false);
  }
  return ErrorCode::NO_ERROR;
}
