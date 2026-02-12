static int make_entry(struct buf *data,
                      const struct buf *value,
                      modseq_t modseq,
                      unsigned char flags)
{
    unsigned long l;
    static const char contenttype[] = "text/plain";
    unsigned long long nmodseq;


    assert(sizeof(modseq_t) <= sizeof(unsigned long long));
    nmodseq = htonll((unsigned long long) modseq);

    l = htonl(value->len);
    buf_appendmap(data, (const char *)&l, sizeof(l));

    buf_appendmap(data, value->s ? value->s : "", value->len);
    buf_putc(data, '\0');


    buf_appendcstr(data, contenttype);
    buf_putc(data, '\0');

    l = 0;
    buf_appendmap(data, (const char *)&l, sizeof(l));


    buf_appendmap(data, (const char *)&nmodseq, sizeof(nmodseq));


    buf_putc(data, flags);

    return 0;
}
