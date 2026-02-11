get_key_paths(char *pri_path, size_t pri_len,
                  char *pub_path, size_t pub_len,
                  const char *kpath, const char *name)
{
    char *path = strdup(kpath);
    size_t len = strlen(path);
    int status = -1;


    if ((len > 0) && (path[len-1] == '/'))
        path[len-1] = '\0';

    if ((access(path, F_OK) != 0) && (mkdir(path, 0700) < 0)) {
        PDP_ERR("Could not create directory '%s'", path);
        goto cleanup;
    }
    if (snprintf(pri_path, pri_len, "%s/%s.pri", path, name) + 1 > pri_len)
        goto cleanup;
    if (snprintf(pub_path, pub_len, "%s/%s.pub", path, name) + 1 > pub_len)
        goto cleanup;
    status = 0;

cleanup:
    free(path);
    return status;
}
