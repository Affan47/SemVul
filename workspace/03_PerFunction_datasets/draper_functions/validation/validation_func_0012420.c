specialists_string(const citizens *specialists)
{
  static char buf[5 * SP_MAX];

  buf[0] = '\0';

  specialist_type_iterate(sp) {
    char *separator = (buf[0] == '\0') ? "" : "/";

    cat_snprintf(buf, sizeof(buf), "%s%d", separator, specialists[sp]);
  } specialist_type_iterate_end;

  return buf;
}
