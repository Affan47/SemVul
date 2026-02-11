lk_karmaUsb_fidToPath(int rio, uint32_t file_id)
{
    int i, len;
    char *path = NULL;

    len = strlen(usbMountPoint) + 17;
    path = malloc(len);
    sprintf(path, "%sfids0/_%.8x", usbMountPoint, file_id);
    len = strlen(path);
    for (i = len; i >= len - 3; i--)
        path[i + 1] = path[i];
    path[len - 3] = '/';
    return path;
}
