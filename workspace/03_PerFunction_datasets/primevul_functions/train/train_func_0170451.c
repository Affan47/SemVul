ssize_t Http2Session::OnDWordAlignedPadding(size_t frameLen,
                                            size_t maxPayloadLen) {
  size_t r = (frameLen + 9) % 8;
  if (r == 0) return frameLen;

  size_t pad = frameLen + (8 - r);


  pad = std::min(maxPayloadLen, pad);
  Debug(this, "using frame size padding: %d", pad);
  return pad;
}
