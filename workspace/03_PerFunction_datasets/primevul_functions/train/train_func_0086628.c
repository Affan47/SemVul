bool OutputFile::open(const String& , const String& ) {
  raise_fatal_error("cannot open a php://output file ");
}
