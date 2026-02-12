inline word* SegmentBuilder::allocate(SegmentWordCount amount) {
  if (intervalLength(pos, ptr.end(), MAX_SEGMENT_WORDS) < amount) {

    return nullptr;
  } else {

    word* result = pos;
    pos = pos + amount;
    return result;
  }
}
