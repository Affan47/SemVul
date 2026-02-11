cache_fallback_scan(Eina_Hash *icons, Eina_Hash *dirs)
{
    unsigned int i;
    Eina_List *xdg_dirs, *l;
    const char *dir;
    char path[PATH_MAX];

    for (i = 0; i < extra_dirs->count; i++)
        cache_fallback_scan_dir(icons, dirs, extra_dirs->data[i]);

    cache_fallback_scan_dir(icons, dirs, efreet_icon_deprecated_user_dir_get());
    cache_fallback_scan_dir(icons, dirs, efreet_icon_user_dir_get());

    xdg_dirs = efreet_data_dirs_get();
    EINA_LIST_FOREACH(xdg_dirs, l, dir)
    {
        snprintf(path, sizeof(path), "%s/icons", dir);
        cache_fallback_scan_dir(icons, dirs, path);
    }

#ifndef STRICT_SPEC
    EINA_LIST_FOREACH(xdg_dirs, l, dir)
    {
        snprintf(path, sizeof(path), "%s/pixmaps", dir);
        cache_fallback_scan_dir(icons, dirs, path);
    }
#endif

    cache_fallback_scan_dir(icons, dirs, "/usr/share/pixmaps");

    return EINA_TRUE;
}
