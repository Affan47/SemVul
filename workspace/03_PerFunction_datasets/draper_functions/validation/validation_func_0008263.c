NYTP_eof(NYTP_file ifile) {
    ERRNO_PROBE;
#ifdef HAS_ZLIB
    if (FILE_STATE(ifile) == NYTP_FILE_INFLATE) {
        return ifile->zlib_at_eof;
    }
#endif
    return feof(ifile->file);
}
