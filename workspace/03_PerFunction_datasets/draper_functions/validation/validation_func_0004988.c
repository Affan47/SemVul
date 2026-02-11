search_dir(
    char *  filename,
    int     searchlocal,
    int     next
)


{
    const char **   incptr;

    incptr = incdir;
#if COMPILER == GNUC
    if (next && **inc_dirp != EOS)
        incptr = inc_dirp + 1;

#endif

    for ( ; incptr < incend; incptr++) {
        if (strlen( *incptr) + strlen( filename) >= PATHMAX)
            cfatal( toolong_fname, *incptr, 0L, filename);
#if SYSTEM == SYS_MAC
        if (incptr == to_search_framework && ! searchlocal) {

            if (search_framework( filename)) {
                if (in_import)
                    do_once( infile->full_fname);
                return  TRUE;
            }

        }
#endif
        if (open_file( incptr, NULL, filename, FALSE, FALSE, FALSE))

            return  TRUE;
    }

    return  FALSE;
}
