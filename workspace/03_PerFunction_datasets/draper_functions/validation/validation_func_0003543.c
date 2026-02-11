fsp_bind_done_all (fsp_link *link)
{
  int sock[link->segments];

  for (fs_segment segment = 0; segment < link->segments; ++segment) {
    unsigned char *out = message_new(FS_BIND_DONE, segment, 0);
    sock[segment] = fsp_write(link, out, 0);
    free(out);
  }

  int errors = 0;

  for (fs_segment segment = 0; segment < link->segments; ++segment) {
    errors += check_message(link, sock[segment], "bind_done(%d) failed: %s");
  }

  return errors;
}
