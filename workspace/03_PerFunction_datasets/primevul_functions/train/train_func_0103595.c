inline bool SegmentBuilder::tryExtend(word* from, word* to) {

  if (pos == from && to <= ptr.end() && to >= from) {
    pos = to;
    return true;
  } else {
    return false;
  }
}
