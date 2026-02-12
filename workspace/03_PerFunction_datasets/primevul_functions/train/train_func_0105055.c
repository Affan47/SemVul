local int bits(struct state *s, int need)
{
    long val;


    val = s->bitbuf;
    while (s->bitcnt < need) {
        if (s->incnt == s->inlen)
            longjmp(s->env, 1);
        val |= long(s->in[s->incnt++]) << s->bitcnt;
        s->bitcnt += 8;
    }


    s->bitbuf = int(val >> need);
    s->bitcnt -= need;


    return int(val & ((1L << need) - 1));
}
