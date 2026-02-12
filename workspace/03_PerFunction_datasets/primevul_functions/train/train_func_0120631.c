int open_input_file(__G)
    __GDEF
{


#ifdef VMS
    G.zipfd = open(G.zipfn, O_RDONLY, 0, OPNZIP_RMS_ARGS);
#else
#ifdef MACOS
    G.zipfd = open(G.zipfn, 0);
#else
#ifdef CMS_MVS
    G.zipfd = vmmvs_open_infile(__G);
#else
#ifdef USE_STRM_INPUT
    G.zipfd = fopen(G.zipfn, FOPR);
#else
    G.zipfd = open(G.zipfn, O_RDONLY | O_BINARY);
#endif
#endif
#endif
#endif

#ifdef USE_STRM_INPUT
    if (G.zipfd == NULL)
#else

    if (G.zipfd == -1)
#endif
    {
        Info(slide, 0x401, ((char *)slide, LoadFarString(CannotOpenZipfile),
          G.zipfn, strerror(errno)));
        return 1;
    }
    return 0;

}
