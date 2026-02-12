void handler(signal)
    int signal;
{
    GETGLOBALS();

#if !(defined(SIGBUS) || defined(SIGSEGV))
    (*G.message)((zvoid *)&G, slide, 0L, 0x41);
#endif

    echon();

#ifdef SIGBUS
    if (signal == SIGBUS) {
        Info(slide, 0x421, ((char *)slide, LoadFarString(ZipfileCorrupt),
          "bus error"));
        DESTROYGLOBALS();
        EXIT(PK_BADERR);
    }
#endif

#ifdef SIGILL
    if (signal == SIGILL) {
        Info(slide, 0x421, ((char *)slide, LoadFarString(ZipfileCorrupt),
          "illegal instruction"));
        DESTROYGLOBALS();
        EXIT(PK_BADERR);
    }
#endif

#ifdef SIGSEGV
    if (signal == SIGSEGV) {
        Info(slide, 0x421, ((char *)slide, LoadFarString(ZipfileCorrupt),
          "segmentation violation"));
        DESTROYGLOBALS();
        EXIT(PK_BADERR);
    }
#endif


    DESTROYGLOBALS();
#if defined(AMIGA) && defined(__SASC)
    _abort();
#endif
    EXIT(IZ_CTRLC);
}
