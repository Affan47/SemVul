aff_create(AFFILE *af)
{
    fwrite(AF_HEADER,1,8,af->aseg);
    aff_toc_build(af);
    af_make_badflag(af);

    const char *version = xstr(PACKAGE_VERSION);
    aff_update_seg(af,AF_AFFLIB_VERSION,0,(const u_char *)version,strlen(version));

#ifdef HAVE_GETPROGNAME
    const char *progname = getprogname();
    if(aff_update_seg(af,AF_CREATOR,0,(const u_char *)progname,strlen(progname))) return -1;
#endif
    if(aff_update_seg(af,AF_AFF_FILE_TYPE,0,(const u_char *)"AFF",3)) return -1;

    return 0;
}
