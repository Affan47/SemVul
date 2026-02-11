netsnmp_is_fqdn(const char *thename)
{
    if (!thename)
        return 0;
    while(*thename) {
        if (*thename != '.' && !isupper((unsigned char)*thename) &&
            !islower((unsigned char)*thename) &&
            !isdigit((unsigned char)*thename) && *thename != '-') {
            return 0;
        }
        thename++;
    }
    return 1;
}
