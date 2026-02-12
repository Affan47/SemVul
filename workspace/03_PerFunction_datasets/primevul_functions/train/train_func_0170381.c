int Http2Session::OnDataChunkReceived(nghttp2_session* handle,
                                      uint8_t flags,
                                      int32_t id,
                                      const uint8_t* data,
                                      size_t len,
                                      void* user_data) {
  Http2Session* session = static_cast<Http2Session*>(user_data);
  Debug(session, "buffering data chunk for stream %d, size: "
        "%d, flags: %d", id, len, flags);
  Environment* env = session->env();
  HandleScope scope(env->isolate());


  if (len == 0)
    return 0;


  CHECK_EQ(nghttp2_session_consume_connection(handle, len), 0);
  Http2Stream* stream = session->FindStream(id);

  if (stream->IsDestroyed())
    return 0;

  stream->statistics_.received_bytes += len;


  do {
    uv_buf_t buf = stream->EmitAlloc(len);
    ssize_t avail = len;
    if (static_cast<ssize_t>(buf.len) < avail)
      avail = buf.len;


    if (LIKELY(buf.base == nullptr))
      buf.base = reinterpret_cast<char*>(const_cast<uint8_t*>(data));
    else
      memcpy(buf.base, data, avail);
    data += avail;
    len -= avail;
    stream->EmitRead(avail, buf);


    if (stream->IsReading())
      nghttp2_session_consume_stream(handle, id, avail);
    else
      stream->inbound_consumed_data_while_paused_ += avail;


    if (session->outgoing_length_ > 4096 ||
        stream->available_outbound_length_ > 4096) {
      session->SendPendingData();
    }
  } while (len != 0);


  if (session->flags_ & SESSION_STATE_WRITE_IN_PROGRESS) {
    CHECK_NE(session->flags_ & SESSION_STATE_READING_STOPPED, 0);
    session->flags_ |= SESSION_STATE_NGHTTP2_RECV_PAUSED;
    Debug(session, "receive paused");
    return NGHTTP2_ERR_PAUSE;
  }

  return 0;
}
