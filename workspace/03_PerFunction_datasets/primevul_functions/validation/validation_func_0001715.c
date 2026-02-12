String HHVM_FUNCTION(hebrev,
                     const String& hebrew_text,
                     int max_chars_per_line ) {
  if (hebrew_text.empty()) return hebrew_text;
  return string_convert_hebrew_string(hebrew_text, max_chars_per_line, false);
}
