shift(Register dst, Immediate shift_amount, int subcode) {
  EnsureSpace ensure_space(this);
  ASSERT(is_uint6(shift_amount.value_));
  if (shift_amount.value_ == 1) {
    emit_rex_64(dst);
    emit(0xD1);
    emit_modrm(subcode, dst);
  } else {
    emit_rex_64(dst);
    emit(0xC1);
    emit_modrm(subcode, dst);
    emit(shift_amount.value_);
  }
}
