globus_libc_memrchr(
    globus_byte_t *                         s,
    globus_byte_t                           c,
    globus_size_t                           n)
{
    globus_byte_t *                         tmp_ptr;

    tmp_ptr = &s[n - 1];
    while(tmp_ptr != s)
    {
        if(*tmp_ptr == c)
        {
            return tmp_ptr;
        }
        tmp_ptr--;
    }

    return NULL;
}
