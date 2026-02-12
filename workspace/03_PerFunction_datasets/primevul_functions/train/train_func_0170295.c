uint8_t Http2Session::SendPendingData() {
  Debug(this, "sending pending data");


  if (IsDestroyed())
    return 0;
  flags_ &= ~SESSION_STATE_WRITE_SCHEDULED;


  if (flags_ & SESSION_STATE_SENDING)
    return 1;

  flags_ |= SESSION_STATE_SENDING;

  ssize_t src_length;
  const uint8_t* src;

  CHECK_EQ(outgoing_buffers_.size(), 0);
  CHECK_EQ(outgoing_storage_.size(), 0);


  while ((src_length = nghttp2_session_mem_send(session_, &src)) > 0) {
    Debug(this, "nghttp2 has %d bytes to send", src_length);
    CopyDataIntoOutgoing(src, src_length);
  }

  CHECK_NE(src_length, NGHTTP2_ERR_NOMEM);

  if (stream_ == nullptr) {


    ClearOutgoing(UV_ECANCELED);
    return 0;
  }


  size_t count = outgoing_buffers_.size();
  if (count == 0) {
    ClearOutgoing(0);
    return 0;
  }
  MaybeStackBuffer<uv_buf_t, 32> bufs;
  bufs.AllocateSufficientStorage(count);


  size_t offset = 0;
  size_t i = 0;
  for (const nghttp2_stream_write& write : outgoing_buffers_) {
    statistics_.data_sent += write.buf.len;
    if (write.buf.base == nullptr) {
      bufs[i++] = uv_buf_init(
          reinterpret_cast<char*>(outgoing_storage_.data() + offset),
          write.buf.len);
      offset += write.buf.len;
    } else {
      bufs[i++] = write.buf;
    }
  }

  chunks_sent_since_last_write_++;

  CHECK_EQ(flags_ & SESSION_STATE_WRITE_IN_PROGRESS, 0);
  flags_ |= SESSION_STATE_WRITE_IN_PROGRESS;
  StreamWriteResult res = underlying_stream()->Write(*bufs, count);
  if (!res.async) {
    flags_ &= ~SESSION_STATE_WRITE_IN_PROGRESS;
    ClearOutgoing(res.err);
  }

  MaybeStopReading();

  return 0;
}
