getNameWithPrefix(const GlobalValue *GV,
                                       bool isImplicitlyPrivate) {
  SmallString<64> Buf;
  getNameWithPrefix(Buf, GV, isImplicitlyPrivate);
  return std::string(Buf.begin(), Buf.end());
}
