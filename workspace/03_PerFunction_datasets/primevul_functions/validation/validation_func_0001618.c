bool WuManberReplacement::initPatterns(const Array& arr) {
  patterns.reserve(arr.size());
  for (ArrayIter iter(arr); iter; ++iter) {
    String pattern = iter.first().toString();
    if (pattern.size() == 0) {
      patterns.clear();
      return false;
    }
    patterns.emplace_back(pattern, iter.second().toString());
  }

  initTables();

  return true;
}
