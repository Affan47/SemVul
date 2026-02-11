wstr_n_from_c(const char *s, size_t length)
{
#if __STDC__ >= 1
        static char     escapes[] = "\aa\bb\ff\nn\rr\tt\vv";
#else
        static char     escapes[] = "\bb\ff\nn\rr\tt";
#endif
        static wchar_t  *buf;
        static size_t   bufmax;
        size_t          remainder;
        const char      *ip;
        wchar_t         *op;


        if (bufmax < length)
        {
                bufmax = length;

                buf = mem_change_size(buf, bufmax * sizeof(wchar_t) * 4);
        }


        language_human();


        mbtowc((wchar_t *)0, (char *)0, 0);


        ip = s;
        op = buf;
        remainder = length;
        while (remainder > 0)
        {
                int             n;

                n = mbtowc(op, ip, remainder);
                if (n == 0)
                        break;
                if (n < 0)
                {
                        char    *esc;


                        esc = strchr(escapes, *ip);
                        if (esc)
                        {
                                *op++ = '\\';
                                *op++ = esc[1];
                        }
                        else
                        {
                                *op++ = '\\';
                                *op++ = '0' + ((*ip >> 6) & 7);
                                *op++ = '0' + ((*ip >> 3) & 7);
                                *op++ = '0' + ( *ip       & 7);
                        }
                        ++ip;
                        --remainder;


                        mbtowc((wchar_t *)0, (char *)0, 0);
                }
                else
                {


                        ip += n;
                        remainder -= n;
                        ++op;
                }
        }


        language_C();


        return wstr_n_from_wc(buf, op - buf);
}
