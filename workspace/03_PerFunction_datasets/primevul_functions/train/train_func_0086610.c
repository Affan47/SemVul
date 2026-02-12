bool OutputFile::seek(int64_t , int  ) {
  raise_warning("cannot seek a php://output stream");
  return false;
}
