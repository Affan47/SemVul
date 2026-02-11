VP8LBitWriterResize(VP8LBitWriter* const bw, size_t extra_size) {
  uint8_t* allocated_buf;
  size_t allocated_size;
  const size_t current_size = VP8LBitWriterNumBytes(bw);
  const uint64_t size_required_64b = (uint64_t)current_size + extra_size;
  const size_t size_required = (size_t)size_required_64b;
  if (size_required != size_required_64b) {
    bw->error_ = 1;
    return 0;
  }
  if (bw->max_bytes_ > 0 && size_required <= bw->max_bytes_) return 1;
  allocated_size = (3 * bw->max_bytes_) >> 1;
  if (allocated_size < size_required) allocated_size = size_required;

  allocated_size = (((allocated_size >> 10) + 1) << 10);
  allocated_buf = (uint8_t*)malloc(allocated_size);
  if (allocated_buf == NULL) {
    bw->error_ = 1;
    return 0;
  }
  memcpy(allocated_buf, bw->buf_, current_size);
  free(bw->buf_);
  bw->buf_ = allocated_buf;
  bw->max_bytes_ = allocated_size;
  memset(allocated_buf + current_size, 0, allocated_size - current_size);
  return 1;
}
