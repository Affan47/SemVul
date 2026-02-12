uv_buf_t Http2StreamListener::OnStreamAlloc(size_t size) {


  return uv_buf_init(nullptr, size);
}
