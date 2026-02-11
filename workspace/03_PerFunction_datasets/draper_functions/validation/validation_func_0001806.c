RCS_check_kflag (const char *arg)
{
    static const char *const  keyword_usage[] =
    {
      "%s %s: invalid RCS keyword expansion mode\n",
      "Valid expansion modes include:\n",
      "   -kkv\tGenerate keywords using the default form.\n",
      "   -kkvl\tLike -kkv, except locker's name inserted.\n",
      "   -kk\tGenerate only keyword names in keyword strings.\n",
      "   -kv\tGenerate only keyword values in keyword strings.\n",
      "   -ko\tGenerate the old keyword string (no changes from checked in file).\n",
      "   -kb\tGenerate binary file unmodified (merges not allowed) (RCS 5.7).\n",
      "(Specify the --help global option for a list of other help options)\n",
      NULL,
    };
    char const *const *cpp = NULL;

    if (arg)
    {
	for (cpp = kflags; *cpp != NULL; cpp++)
	{
	    if (STREQ (arg, *cpp))
		break;
	}
    }

    if (arg == NULL || *cpp == NULL)
    {
	usage (keyword_usage);
    }

    return Xasprintf ("-k%s", *cpp);
}
