int Http2Stream::SubmitTrailers(nghttp2_nv* nva, size_t len) {
  CHECK(!this->IsDestroyed());
  Http2Scope h2scope(this);
  Debug(this, "sending %d trailers", len);
  int ret;


  if (len == 0) {
    Http2Stream::Provider::Stream prov(this, 0);
    ret = nghttp2_submit_data(**session_, NGHTTP2_FLAG_END_STREAM, id_, *prov);
  } else {
    ret = nghttp2_submit_trailer(**session_, id_, nva, len);
  }
  CHECK_NE(ret, NGHTTP2_ERR_NOMEM);
  return ret;
}
