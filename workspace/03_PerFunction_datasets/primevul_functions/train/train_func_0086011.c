bool HTTP2Codec::parsingTrailers() const {


  if (curHeader_.type == http2::FrameType::HEADERS ||
      curHeader_.type == http2::FrameType::CONTINUATION) {
    if (transportDirection_ == TransportDirection::DOWNSTREAM) {
      return parsingDownstreamTrailers_;
    } else {
      return !decodeInfo_.hasStatus();
    }
  }
  return false;
}
