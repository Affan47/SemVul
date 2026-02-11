chrootDirective(MaState *state, cchar *key, cchar *value)
{
#if BLD_UNIX_LIKE
    char    *path;
    path = httpMakePath(state->route, value);
    if (chdir(path) < 0) {
        mprError("Can't change working directory to %s", path);
        return MPR_ERR_CANT_OPEN;
    }
    if (chroot(path) < 0) {
        if (errno == EPERM) {
            mprError("Must be super user to use the --chroot option\n");
        } else {
            mprError("Can't change change root directory to %s, errno %d\n", path, errno);
        }
        return MPR_ERR_BAD_SYNTAX;
    }
    mprLog(MPR_CONFIG, "Chroot to: \"%s\"", path);
    return 0;
#else
    mprError("Chroot directive not supported on this operating system\n");
    return MPR_ERR_BAD_SYNTAX;
#endif
}
