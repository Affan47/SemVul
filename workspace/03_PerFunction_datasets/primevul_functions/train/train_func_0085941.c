folly::Optional<ErrorCode> HTTP2Codec::parseHeadersCheckConcurrentStreams(
    const folly::Optional<http2::PriorityUpdate>& priority) {
  if (curHeader_.type == http2::FrameType::HEADERS ||
      curHeader_.type == http2::FrameType::EX_HEADERS) {
    if (curHeader_.flags & http2::PRIORITY) {
      DCHECK(priority);

    }


    if (callback_->numIncomingStreams() >=
        egressSettings_.getSetting(SettingsId::MAX_CONCURRENT_STREAMS,
                                   std::numeric_limits<int32_t>::max())) {
      streamError(folly::to<string>("Exceeded max_concurrent_streams"),
                  ErrorCode::REFUSED_STREAM, true);
      return ErrorCode::NO_ERROR;
    }
  }
  return folly::Optional<ErrorCode>();
}
