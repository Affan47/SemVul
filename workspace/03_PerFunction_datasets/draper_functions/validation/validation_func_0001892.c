__lzo_init_v2(unsigned v, int s1, int s2, int s3, int s4, int s5,
                          int s6, int s7, int s8, int s9)
{
    int r;

#if defined(__LZO_IN_MINILZO)
#elif (LZO_CC_MSC && ((_MSC_VER) < 700))
#else
#define ACC_WANT_ACC_CHK_CH 1
#undef ACCCHK_ASSERT
#define ACCCHK_ASSERT(expr)  LZO_COMPILE_TIME_ASSERT(expr)
#endif
#undef ACCCHK_ASSERT

    if (v == 0)
        return LZO_E_ERROR;

    r = (s1 == -1 || s1 == (int) sizeof(short)) &&
        (s2 == -1 || s2 == (int) sizeof(int)) &&
        (s3 == -1 || s3 == (int) sizeof(long)) &&
        (s4 == -1 || s4 == (int) sizeof(lzo_uint32)) &&
        (s5 == -1 || s5 == (int) sizeof(lzo_uint)) &&
        (s6 == -1 || s6 == (int) lzo_sizeof_dict_t) &&
        (s7 == -1 || s7 == (int) sizeof(char *)) &&
        (s8 == -1 || s8 == (int) sizeof(lzo_voidp)) &&
        (s9 == -1 || s9 == (int) sizeof(lzo_callback_t));
    if (!r)
        return LZO_E_ERROR;

    r = _lzo_config_check();
    if (r != LZO_E_OK)
        return r;

    return r;
}
