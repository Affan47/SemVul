static Jsi_Wide jsi_strtoul(const char *str, char **endptr)
{
#ifdef JSI__LONG_LONG
    int sign;
    int base;
    int i = JsiNumberBase(str, &base, &sign);

    if (base != 10) {
        Jsi_Wide value = strtoul(str + i, endptr, base);
        if (endptr == NULL || *endptr != str + i) {
            return value * sign;
        }
    }


    return strtoul(str, endptr, 10);
#else
    return (unsigned long)jsi_strtol(str, endptr);
#endif
}
