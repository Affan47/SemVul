ErrorCode HTTP2Codec::parseWindowUpdate(Cursor& cursor) {
  VLOG(4) << "parsing WINDOW_UPDATE frame for stream=" << curHeader_.stream <<
    " length=" << curHeader_.length;
  uint32_t delta = 0;
  auto err = http2::parseWindowUpdate(cursor, curHeader_, delta);
  RETURN_IF_ERROR(err);
  if (delta == 0) {
    VLOG(4) << "Invalid 0 length delta for stream=" << curHeader_.stream;
    if (curHeader_.stream == 0) {
      goawayErrorMessage_ = folly::to<string>(
        "GOAWAY error: invalid/0 length delta for streamID=",
        curHeader_.stream);
      return ErrorCode::PROTOCOL_ERROR;
    } else {


      goawayErrorMessage_ = folly::to<string>(
        "parseWindowUpdate Invalid 0 length");
      VLOG(4) << goawayErrorMessage_;
      streamError(folly::to<std::string>("streamID=", curHeader_.stream,
                                         " with HTTP2Codec stream error: ",
                                         "window update delta=", delta),
                  ErrorCode::PROTOCOL_ERROR);
      return ErrorCode::PROTOCOL_ERROR;
    }
  }


  deliverCallbackIfAllowed(&HTTPCodec::Callback::onWindowUpdate,
                           "onWindowUpdate", curHeader_.stream, delta);
  return ErrorCode::NO_ERROR;
}
