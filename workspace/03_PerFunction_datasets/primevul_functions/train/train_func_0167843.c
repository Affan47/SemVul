cmd_spec_dirstruct (const char *com, const char *val, void *place_ignored _GL_UNUSED)
{
  if (!cmd_boolean (com, val, &opt.dirstruct))
    return false;


  if (opt.dirstruct)
    opt.no_dirstruct = false;
  else
    opt.no_dirstruct = true;
  return true;
}
