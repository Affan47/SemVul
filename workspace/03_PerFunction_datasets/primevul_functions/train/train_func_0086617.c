bool OutputFile::truncate(int64_t ) {
  raise_warning("cannot truncate a php://output stream");
  return false;
}
