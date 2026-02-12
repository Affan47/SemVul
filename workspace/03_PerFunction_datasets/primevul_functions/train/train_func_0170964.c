int Http2Session::OnSendData(
      nghttp2_session* session_,
      nghttp2_frame* frame,
      const uint8_t* framehd,
      size_t length,
      nghttp2_data_source* source,
      void* user_data) {
  Http2Session* session = static_cast<Http2Session*>(user_data);
  BaseObjectPtr<Http2Stream> stream = session->FindStream(frame->hd.stream_id);
  if (!stream) return 0;


  session->CopyDataIntoOutgoing(framehd, 9);
  if (frame->data.padlen > 0) {
    uint8_t padding_byte = frame->data.padlen - 1;
    CHECK_EQ(padding_byte, frame->data.padlen - 1);
    session->CopyDataIntoOutgoing(&padding_byte, 1);
  }

  Debug(session, "nghttp2 has %d bytes to send directly", length);
  while (length > 0) {


    CHECK(!stream->queue_.empty());

    NgHttp2StreamWrite& write = stream->queue_.front();
    if (write.buf.len <= length) {

      length -= write.buf.len;
      session->PushOutgoingBuffer(std::move(write));
      stream->queue_.pop();
      continue;
    }


    session->PushOutgoingBuffer(NgHttp2StreamWrite {
      uv_buf_init(write.buf.base, length)
    });
    write.buf.base += length;
    write.buf.len -= length;
    break;
  }

  if (frame->data.padlen > 0) {

    session->PushOutgoingBuffer(NgHttp2StreamWrite {
      uv_buf_init(const_cast<char*>(zero_bytes_256), frame->data.padlen - 1)
    });
  }

  return 0;
}
