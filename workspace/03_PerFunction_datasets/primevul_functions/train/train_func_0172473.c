static int opt_strings_flags(
    char_u *val,
    char **values,
    unsigned *flagp,
    bool list
)
{
  unsigned int new_flags = 0;

  while (*val) {
    for (unsigned int i = 0;; ++i) {
      if (values[i] == NULL)
        return FAIL;

      size_t len = STRLEN(values[i]);
      if (STRNCMP(values[i], val, len) == 0
          && ((list && val[len] == ',') || val[len] == NUL)) {
        val += len + (val[len] == ',');
        assert(i < sizeof(1U) * 8);
        new_flags |= (1U << i);
        break;
      }
    }
  }
  if (flagp != NULL)
    *flagp = new_flags;

  return OK;
}
