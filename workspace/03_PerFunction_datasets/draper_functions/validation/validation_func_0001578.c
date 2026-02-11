do_error (buf, limit, op, keyword)
     U_CHAR *buf, *limit;
     FILE_BUF *op ATTRIBUTE_UNUSED;
     struct directive *keyword ATTRIBUTE_UNUSED;
{
  int length = limit - buf;
  U_CHAR *copy = (U_CHAR *) alloca (length + 1);
  bcopy ((char *) buf, (char *) copy, length);
  copy[length] = 0;
  SKIP_WHITE_SPACE (copy);
  error ("#error %s", copy);
  return 0;
}
