VP8LFillBitWindow(VP8LBitReader* const br) {
  if (br->bit_pos_ >= WBITS) {
#if (defined(__x86_64__) || defined(_M_X64))
    if (br->pos_ + sizeof(br->val_) < br->len_) {
      br->val_ >>= WBITS;
      br->bit_pos_ -= WBITS;


      br->val_ |= *(const vp8l_val_t*)(br->buf_ + br->pos_) << (LBITS - WBITS);
      br->pos_ += LOG8_WBITS;
      return;
    }
#endif
    ShiftBytes(br);
    br->eos_ = IsEndOfStreamSpecial(br);
  }
}
