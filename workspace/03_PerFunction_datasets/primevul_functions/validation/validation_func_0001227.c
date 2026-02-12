String HHVM_FUNCTION(socket_strerror,
                     int errnum) {


  if (errnum < -10000) {
    errnum = (-errnum) - 10000;
#if HAVE_HSTRERROR
    return String(hstrerror(errnum), CopyString);
#endif
    return folly::format("Host lookup error {}", errnum).str();
  }

  return String(folly::errnoStr(errnum));
}
