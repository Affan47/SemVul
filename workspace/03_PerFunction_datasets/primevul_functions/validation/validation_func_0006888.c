parse_OUTPUT_TRUNC(const char *arg,
                   const struct ofpact_parse_params *pp OVS_UNUSED)
{


    return xasprintf("unknown action %s", arg);
}
