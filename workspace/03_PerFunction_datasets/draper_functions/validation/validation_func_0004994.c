icudebug (puuconf, argc, argv, pvar, pinfo)
     pointer puuconf ATTRIBUTE_UNUSED;
     int argc ATTRIBUTE_UNUSED;
     char **argv ATTRIBUTE_UNUSED;
     pointer pvar ATTRIBUTE_UNUSED;
     pointer pinfo ATTRIBUTE_UNUSED;
{
#if DEBUG > 1
  if (iDebug != 0)
    iDebug = 0;
  else
    iDebug = DEBUG_MAX;
#else
  ucuputs ("[compiled without debugging]");
#endif
  return UUCONF_CMDTABRET_CONTINUE;
}
