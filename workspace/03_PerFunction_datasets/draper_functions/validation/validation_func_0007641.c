Flush() {
  do {
    zerror_ = Deflate(Z_FULL_FLUSH);
  } while (zerror_ == Z_OK);
  return zerror_ == Z_OK;
}
