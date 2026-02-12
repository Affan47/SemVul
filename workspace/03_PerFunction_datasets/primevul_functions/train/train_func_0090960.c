void FontData::Bound(int32_t offset, int32_t length) {

  CHECK(offset >= 0);
  CHECK(length >= 0);


  CHECK(bound_offset_ <= std::numeric_limits<int32_t>::max() - offset);
  const int32_t new_offset = bound_offset_ + offset;

  if (length == GROWABLE_SIZE) {


    CHECK(new_offset <= array_->Size());
  } else {


    CHECK(new_offset <= array_->Size() - length);
  }

  bound_offset_ = new_offset;
  bound_length_ = length;
}
