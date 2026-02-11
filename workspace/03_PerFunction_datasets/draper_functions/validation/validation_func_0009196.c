ParseCharacterClass() {
  static const char* kUnterminated = "Unterminated character class";
  static const char* kRangeOutOfOrder = "Range out of order in character class";

  ASSERT_EQ(current(), '[');
  Advance();
  bool is_negated = false;
  if (current() == '^') {
    is_negated = true;
    Advance();
  }
  ZoneList<CharacterRange>* ranges = new(zone()) ZoneList<CharacterRange>(2);
  while (has_more() && current() != ']') {
    uc16 char_class = kNoCharClass;
    CharacterRange first = ParseClassAtom(&char_class CHECK_FAILED);
    if (current() == '-') {
      Advance();
      if (current() == kEndMarker) {


        break;
      } else if (current() == ']') {
        AddRangeOrEscape(ranges, char_class, first);
        ranges->Add(CharacterRange::Singleton('-'));
        break;
      }
      uc16 char_class_2 = kNoCharClass;
      CharacterRange next = ParseClassAtom(&char_class_2 CHECK_FAILED);
      if (char_class != kNoCharClass || char_class_2 != kNoCharClass) {

        AddRangeOrEscape(ranges, char_class, first);
        ranges->Add(CharacterRange::Singleton('-'));
        AddRangeOrEscape(ranges, char_class_2, next);
        continue;
      }
      if (first.from() > next.to()) {
        return ReportError(CStrVector(kRangeOutOfOrder) CHECK_FAILED);
      }
      ranges->Add(CharacterRange::Range(first.from(), next.to()));
    } else {
      AddRangeOrEscape(ranges, char_class, first);
    }
  }
  if (!has_more()) {
    return ReportError(CStrVector(kUnterminated) CHECK_FAILED);
  }
  Advance();
  if (ranges->length() == 0) {
    ranges->Add(CharacterRange::Everything());
    is_negated = !is_negated;
  }
  return new(zone()) RegExpCharacterClass(ranges, is_negated);
}
