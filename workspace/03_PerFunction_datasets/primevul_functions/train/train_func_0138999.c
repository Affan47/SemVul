static void libopenjpeg_error_callback(const char *msg, void * ) {
  error(errSyntaxError, -1, "{0:s}", msg);
}
