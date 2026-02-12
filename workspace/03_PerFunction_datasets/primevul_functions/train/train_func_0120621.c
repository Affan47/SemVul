int seek_zipf(__G__ abs_offset)
    __GDEF
    zoff_t abs_offset;
{


    zoff_t request = abs_offset + G.extra_bytes;
    zoff_t inbuf_offset = request % INBUFSIZ;
    zoff_t bufstart = request - inbuf_offset;

    if (request < 0) {
        Info(slide, 1, ((char *)slide, LoadFarStringSmall(SeekMsg),
             G.zipfn, LoadFarString(ReportMsg)));
        return(PK_BADERR);
    } else if (bufstart != G.cur_zipfile_bufstart) {
        Trace((stderr,
          "fpos_zip: abs_offset = %s, G.extra_bytes = %s\n",
          FmZofft(abs_offset, NULL, NULL),
          FmZofft(G.extra_bytes, NULL, NULL)));
#ifdef USE_STRM_INPUT
        zfseeko(G.zipfd, bufstart, SEEK_SET);
        G.cur_zipfile_bufstart = zftello(G.zipfd);
#else
        G.cur_zipfile_bufstart = zlseek(G.zipfd, bufstart, SEEK_SET);
#endif
        Trace((stderr,
          "       request = %s, (abs+extra) = %s, inbuf_offset = %s\n",
          FmZofft(request, NULL, NULL),
          FmZofft((abs_offset+G.extra_bytes), NULL, NULL),
          FmZofft(inbuf_offset, NULL, NULL)));
        Trace((stderr, "       bufstart = %s, cur_zipfile_bufstart = %s\n",
          FmZofft(bufstart, NULL, NULL),
          FmZofft(G.cur_zipfile_bufstart, NULL, NULL)));
        if ((G.incnt = read(G.zipfd, (char *)G.inbuf, INBUFSIZ)) <= 0)
            return(PK_EOF);
        G.incnt -= (int)inbuf_offset;
        G.inptr = G.inbuf + (int)inbuf_offset;
    } else {
        G.incnt += (G.inptr-G.inbuf) - (int)inbuf_offset;
        G.inptr = G.inbuf + (int)inbuf_offset;
    }
    return(PK_OK);
}
