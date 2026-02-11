RegisterEnumExtension(const MessageLite* containing_type,
                                         int number, FieldType type,
                                         bool is_repeated, bool is_packed,
                                         EnumValidityFunc* is_valid) {
  GOOGLE_CHECK_EQ(type, WireFormatLite::TYPE_ENUM);
  ExtensionInfo info(type, is_repeated, is_packed);
  info.enum_validity_check.func = CallNoArgValidityFunc;

  info.enum_validity_check.arg = (void*)is_valid;
  Register(containing_type, number, info);
}
