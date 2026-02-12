bool pcre_literal_data::matches(const StringData* subject,
                                int pos,
                                int* offsets) const {
  assertx(isLiteral());
  assertx(pos >= 0);


  if (subject->size() < literal_str->length() + pos) {
    return false;
  }

  size_t literal_strlen = literal_str->length();
  auto const subject_c = subject->data();
  auto const literal_c = literal_str->c_str();
  if (match_start) {

    if (pos || (match_end && subject->size() != literal_strlen)) {
      return false;
    }


    if (case_insensitive ?
        bstrcaseeq(subject_c, literal_c, literal_strlen) :
        memcmp(subject_c, literal_c, literal_strlen) == 0) {
      offsets[0] = 0;
      offsets[1] = literal_strlen * sizeof(char);
      return true;
    }
  } else if (match_end) {

    auto const subject_tail = subject_c + (subject->size() - literal_strlen);
    if (case_insensitive ?
        bstrcaseeq(subject_tail, literal_c, literal_strlen) :
        memcmp(subject_tail, literal_c, literal_strlen) == 0) {
      offsets[0] = (subject->size() - literal_strlen) * sizeof(char);
      offsets[1] = subject->size() * sizeof(char);
      return true;
    }
  } else {
    if (!literal_strlen) {
      offsets[0] = offsets[1] = pos;
      return true;
    }

    auto const subject_str = StrNR(subject);
    auto const find_response = subject_str.asString().find(
      *literal_str, pos, !case_insensitive);
    if (find_response >= 0) {
      offsets[0] = find_response * sizeof(char);
      offsets[1] = offsets[0] + literal_strlen * sizeof(char);
      return true;
    }
  }
  return false;
}
