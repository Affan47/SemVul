gt_cge_spacedseed_runner(GT_UNUSED int argc,
                                    GT_UNUSED const char **argv,
                                    GT_UNUSED int parsed_args,
                                    void *tool_arguments,
                                    GtError *err)
{
  Cge_spacedseed_options *arguments = tool_arguments;
  GtLogger *logger = NULL;
  bool haserr = false;

  gt_assert(parsed_args == argc);
  logger = gt_logger_new(arguments->verbose, GT_LOGGER_DEFLT_PREFIX, stdout);
  if (arguments->verbose)
  {
    unsigned long idx;

    printf("# %sindex=%s\n",arguments->withesa ? "esa" : "pck",
                            gt_str_get(arguments->str_inputindex));
    for (idx = 0; idx < gt_str_array_size(arguments->queryfilenames); idx++)
    {
      printf("# queryfile=%s\n",
             gt_str_array_get(arguments->queryfilenames,idx));
    }
  }
  if (gt_matchspacedseed(arguments->withesa,
                      arguments->docompare,
                      gt_str_get(arguments->str_inputindex),
                      arguments->queryfilenames,
                      arguments->verbose,
                      err) != 0)
  {
    haserr = true;
  }
  gt_logger_delete(logger);
  return haserr ? - 1 : 0;
}
