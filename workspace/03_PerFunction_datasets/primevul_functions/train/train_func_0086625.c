int64_t OutputFile::readImpl(char* , int64_t ) {
  raise_warning("cannot read from a php://output stream");
  return 0;
}
