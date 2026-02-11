dbg(int l, const char* msg, ...)
{
  va_list ap;
  va_start(ap, msg);
  if (global_opts.debug_level >= l) {
    vfprintf(stderr,msg, ap);
    fflush(stderr);
  }
  va_end(ap);
}
