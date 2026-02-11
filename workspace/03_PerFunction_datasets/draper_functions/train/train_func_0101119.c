strscan_peek(VALUE self, VALUE vlen)
{
    struct strscanner *p;
    long len;

    GET_SCANNER(self, p);

    len = NUM2LONG(vlen);
    if (EOS_P(p))
        return infect(str_new(p, "", 0), p);

    if (p->curr + len > S_LEN(p))
        len = S_LEN(p) - p->curr;
    return extract_beg_len(p, p->curr, len);
}
