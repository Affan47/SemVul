get_crypt_method(buf)
    buf_T *buf;
{
    return crypt_method_from_string(*buf->b_p_cm == NUL ? p_cm : buf->b_p_cm);
}
