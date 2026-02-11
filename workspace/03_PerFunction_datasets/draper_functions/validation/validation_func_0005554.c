Jim_PwdCmd(Jim_Interp *interp, int argc, Jim_Obj *const *argv)
{
    const int cwd_len = 2048;
    char *cwd = malloc(cwd_len);

    if (getcwd(cwd, cwd_len) == NULL) {
        Jim_SetResultString(interp, "Failed to get pwd", -1);
        return JIM_ERR;
    }
#if defined(__MINGW32__) || defined(_MSC_VER)
    {

        char *p = cwd;
        while ((p = strchr(p, '\\')) != NULL) {
            *p++ = '/';
        }
    }
#endif

    Jim_SetResultString(interp, cwd, -1);

    free(cwd);
    return JIM_OK;
}
