ffi2c(LONGLONG ival,
          char *cval,
          int *status)


{
    if (*status > 0)
        return(*status);

    cval[0] = '\0';

#if defined(_MSC_VER)

    if (sprintf(cval, "%I64d", ival) < 0)

#elif (USE_LL_SUFFIX == 1)
    if (sprintf(cval, "%lld", ival) < 0)
#else
    if (sprintf(cval, "%ld", ival) < 0)
#endif
    {
        ffpmsg("Error in ffi2c converting integer to string");
        *status = BAD_I2C;
    }
    return(*status);
}
