native(SmallVectorImpl<char> &Path) {
#ifdef LLVM_ON_WIN32
  std::replace(Path.begin(), Path.end(), '/', '\\');
#else
  for (auto PI = Path.begin(), PE = Path.end(); PI < PE; ++PI) {
    if (*PI == '\\') {
      auto PN = PI + 1;
      if (PN < PE && *PN == '\\')
        ++PI;
      else
        *PI = '/';
    }
  }
#endif
}
