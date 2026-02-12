void UnicodeString::swap(UnicodeString &other) U_NOEXCEPT {
  UnicodeString temp;

  temp.copyFieldsFrom(*this, FALSE);
  this->copyFieldsFrom(other, FALSE);
  other.copyFieldsFrom(temp, FALSE);

  temp.fUnion.fFields.fLengthAndFlags = kShortString;
}
