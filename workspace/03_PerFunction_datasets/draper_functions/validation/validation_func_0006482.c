createFilter(int opid __attribute__ ((__unused__)), char *value __attribute__ ((__unused__)))
{
    logger(LG_INFO, "Sorry. No filtering on macro columns implemented yet");
    return new AndingFilter();
}
