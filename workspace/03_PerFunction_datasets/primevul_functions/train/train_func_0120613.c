int fillinbuf(__G)
    __GDEF
{
    if (G.mem_mode ||
                  (G.incnt = read(G.zipfd, (char *)G.inbuf, INBUFSIZ)) <= 0)
        return 0;
    G.cur_zipfile_bufstart += INBUFSIZ;
    G.inptr = G.inbuf;
    defer_leftover_input(__G);

#if CRYPT
    if (G.pInfo->encrypted) {
        uch *p;
        int n;

        for (n = G.incnt, p = G.inptr;  n--;  p++)
            zdecode(*p);
    }
#endif

    return G.incnt;

}
