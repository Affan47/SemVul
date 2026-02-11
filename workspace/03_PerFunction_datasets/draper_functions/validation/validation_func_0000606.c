unibyte_str2int(const uchar *src, size_t len, ScmMultibyteState state)
{
#if SCM_STRICT_ENCODING_CHECK
    if (len != 1)
        return SCM_ICHAR_EOF;
#endif
    return src[0];
}
