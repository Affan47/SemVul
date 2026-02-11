set_handle_alignment(int align) {
  CHECK(align > 0 && 0 == (align & (align - 1)));
  CHECK(static_cast<size_t>(align) < block_size_);
  CHECK((block_size_ % align) == 0);
  CHECK(is_empty());
  handle_alignment_ = align;
  handle_alignment_bits_ = 0;
  while ((1 << handle_alignment_bits_) < handle_alignment_) {
    ++handle_alignment_bits_;
  }
}
