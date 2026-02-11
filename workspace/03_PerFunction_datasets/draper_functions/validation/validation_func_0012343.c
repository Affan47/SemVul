gt_xvfprintf(FILE *stream, const char *format, va_list ap)
{
  if (vfprintf(stream, format, ap) < 0) {
    perror("cannot vfprintf");
    exit(EXIT_FAILURE);
  }
}
