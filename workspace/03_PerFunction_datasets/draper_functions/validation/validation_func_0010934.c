SerializeMessageSetWithCachedSizes(
    io::CodedOutputStream* output) const {
  map<int, Extension>::const_iterator iter;
  for (iter = extensions_.begin(); iter != extensions_.end(); ++iter) {
    iter->second.SerializeMessageSetItemWithCachedSizes(iter->first, output);
  }
}
