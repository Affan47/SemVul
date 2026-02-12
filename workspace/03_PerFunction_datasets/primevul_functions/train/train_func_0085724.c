Variant StringUtil::ChunkSplit(const String& body, int chunklen ,
                               const String& end ) {
  if (chunklen <= 0) {
    throw_invalid_argument("chunklen: (non-positive)");
    return false;
  }

  String ret;
  int len = body.size();
  if (chunklen >= len) {
    ret = body;
    ret += end;
  } else {
    return string_chunk_split(body.data(), len, end.c_str(),
                              end.size(), chunklen);
  }
  return ret;
}
