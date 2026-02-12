uchar Utf8::ValueOf(const byte* bytes, unsigned length, unsigned* cursor) {
  if (length <= 0) return kBadChar;
  byte first = bytes[0];

  if (first <= kMaxOneByteChar) {
    *cursor += 1;
    return first;
  }
  return CalculateValue(bytes, length, cursor);
}
