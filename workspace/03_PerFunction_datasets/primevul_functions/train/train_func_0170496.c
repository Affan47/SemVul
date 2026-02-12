void Http2Session::CopyDataIntoOutgoing(const uint8_t* src, size_t src_length) {
  size_t offset = outgoing_storage_.size();
  outgoing_storage_.resize(offset + src_length);
  memcpy(&outgoing_storage_[offset], src, src_length);


  PushOutgoingBuffer(nghttp2_stream_write {
    uv_buf_init(nullptr, src_length)
  });
}
