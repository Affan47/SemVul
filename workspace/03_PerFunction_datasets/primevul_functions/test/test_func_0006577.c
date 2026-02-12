do_test (void)
{
  char *base = support_create_and_chdir_toolong_temp_directory (BASENAME);

  char buf[PATH_MAX + 1];
  const char *res = realpath (".", buf);


  TEST_VERIFY (res == NULL);
  TEST_VERIFY (errno == ENAMETOOLONG);

  free (base);
  return 0;
}
