rfio_HsmIf_rmdir(const char *path) {
    int rc = -1;

#if defined(CNS_ROOT)
    if ( rfio_HsmIf_IsCnsFile(path) ) {
        rc = Cns_rmdir(path);
    }
#endif
    return(rc);
}
