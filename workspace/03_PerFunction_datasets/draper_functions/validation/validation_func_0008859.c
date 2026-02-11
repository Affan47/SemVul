MergeFrom(const MessageOptions& from) {
  GOOGLE_CHECK_NE(&from, this);
  uninterpreted_option_.MergeFrom(from.uninterpreted_option_);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_message_set_wire_format()) {
      set_message_set_wire_format(from.message_set_wire_format());
    }
    if (from.has_no_standard_descriptor_accessor()) {
      set_no_standard_descriptor_accessor(from.no_standard_descriptor_accessor());
    }
  }
  _extensions_.MergeFrom(from._extensions_);
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}
