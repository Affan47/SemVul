sequence(UDF_INIT *initid __attribute__((unused)), UDF_ARGS *args,
                  char *is_null __attribute__((unused)),
                  char *error __attribute__((unused)))
{
  ulonglong val=0;
  if (args->arg_count)
    val= *((longlong*) args->args[0]);
  return ++*((longlong*) initid->ptr) + val;
}
