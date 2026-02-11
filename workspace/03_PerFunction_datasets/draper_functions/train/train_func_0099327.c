word_end(int pos) const {

  while (pos < length() && (isalnum(char_at(pos)) || char_at(pos) == '_'))
  {
    pos = next_char(pos);
  }
  return pos;
}
