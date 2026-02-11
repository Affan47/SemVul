genders_strerror_functionality(int verbose)
{
  genders_t handle;
  int errcount = 0;
  int num = 0;
  int i = 0;

  if (!(handle = genders_handle_create()))
    genders_err_exit("genders_handle_create");

  if (genders_load_data(handle, genders_database_base.filename) < 0)
    genders_err_exit("genders_load_data: %s", genders_errormsg(handle));

  for (i = GENDERS_ERR_SUCCESS; i <= GENDERS_ERR_ERRNUMRANGE; i++)
    {
      char *expected_string, *string;
      int err;

      genders_set_errnum(handle, i);
      expected_string = genders_errormsg(handle);
      string = genders_strerror(i);

      err = genders_string_check("genders_strerror",
				 num,
				 expected_string,
				 "expected_string",
				 string,
				 "string",
				 NULL,
				 verbose);

      errcount += err;
      num++;
    }

  if (genders_handle_destroy(handle) < 0)
    genders_err_exit("genders_handle_destroy");

  return errcount;
}
