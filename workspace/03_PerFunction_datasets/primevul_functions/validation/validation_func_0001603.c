int64_t MemFile::writeImpl(const char* , int64_t ) {
  raise_fatal_error((std::string("cannot write a mem stream: ") +
                             getName()).c_str());
}
