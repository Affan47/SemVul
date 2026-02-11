parsemkfmindex(Mkfmcallinfo *mkfmcallinfo,
                               int argc,
                               const char **argv,
                               GtError *err)
{
  GtOptionParser *op;
  GtOption *option, *optionfmout;
  GtOPrval oprval;
  int parsed_args;

  gt_error_check(err);
  mkfmcallinfo->indexnametab = gt_str_array_new();
  mkfmcallinfo->outfmindex = gt_str_new();
  mkfmcallinfo->leveldesc = gt_str_new();
  op = gt_option_parser_new("[option ...] -ii indexfile [...]",
                         "Compute FM-index.");
  gt_option_parser_set_mail_address(op, "<kurtz@zbh.uni-hamburg.de>");
  optionfmout = gt_option_new_string("fmout",
                             "specify name of FM-index to be generated\n"
                             "(mandatory if more than one input index "
                             "is specified)",
                             mkfmcallinfo->outfmindex, NULL);
  gt_option_parser_add_option(op, optionfmout);

  option = gt_option_new_filename_array("ii", "specify indices to be used",
                                        mkfmcallinfo->indexnametab);
  gt_option_is_mandatory(option);
  gt_option_parser_add_option(op, option);

  option = gt_option_new_string("size",
                             "specify size (tiny, small, medium, big)",
                             mkfmcallinfo->leveldesc, "medium");
  gt_option_parser_add_option(op, option);

  option = gt_option_new_bool("noindexpos",
                           "store no index positions (hence the positions of\n"
                           "matches in the index cannot be retrieved)",
                           &mkfmcallinfo->noindexpos,false);
  gt_option_parser_add_option(op, option);

  oprval = gt_option_parser_parse(op, &parsed_args, argc, argv, gt_versionfunc,
                                  err);
  if (oprval == GT_OPTION_PARSER_OK)
  {
    if (!gt_option_is_set(optionfmout))
    {
      if (gt_str_array_size(mkfmcallinfo->indexnametab) > 1UL)
      {
        gt_error_set(err,"if more than one index is given, then "
                          "option -fmout is mandatory");
        oprval = GT_OPTION_PARSER_ERROR;
      } else
      {
        char *basenameptr;

        basenameptr = gt_basename(gt_str_array_get(mkfmcallinfo->indexnametab,
                                  0));
        gt_str_set(mkfmcallinfo->outfmindex,basenameptr);
        gt_free(basenameptr);
      }
    }
  }
  gt_option_parser_delete(op);
  if (oprval == GT_OPTION_PARSER_OK && parsed_args != argc)
  {
    gt_error_set(err,"superfluous program parameters");
    oprval = GT_OPTION_PARSER_ERROR;
  }
  return oprval;
}
