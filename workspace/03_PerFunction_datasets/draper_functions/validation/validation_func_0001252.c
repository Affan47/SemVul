globus_l_gfs_getpwnam(
    const char *                        name)
{
    int                                 rc;
    int                                 pw_buflen;
    char *                              pw_buffer;
    struct passwd                       pwent_mem;
    struct passwd *                     pw_result;
    struct passwd *                     pwent = NULL;

#ifdef _SC_GETPW_R_SIZE_MAX
    pw_buflen = sysconf(_SC_GETPW_R_SIZE_MAX) + 1;
    if(pw_buflen < 1)
    {
        pw_buflen = 1024;
    }
#else
    pw_buflen = 1024;
#endif
    pw_buffer = globus_malloc(pw_buflen);
    if(!pw_buffer)
    {
        return NULL;
    }

    rc = globus_libc_getpwnam_r(
        (char *)name, &pwent_mem, pw_buffer, pw_buflen, &pw_result);
    if(rc != 0 || pw_result == NULL)
    {
        globus_free(pw_buffer);
        return NULL;
    }

    pwent = globus_l_gfs_pw_copy(pw_result);
    globus_free(pw_buffer);

    return pwent;
}
