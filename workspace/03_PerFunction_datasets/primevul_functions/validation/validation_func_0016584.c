ly_load_plugins_dir(DIR *dir, const char *dir_path, int ext_or_type)
{
    struct dirent *file;
    size_t len;
    char *str, *name;
    void *dlhandler;
    int ret;

#ifdef STATIC
    return;
#endif

    while ((file = readdir(dir))) {

        len = strlen(file->d_name);
        if (len < LY_PLUGIN_SUFFIX_LEN + 1 ||
                strcmp(&file->d_name[len - LY_PLUGIN_SUFFIX_LEN], LY_PLUGIN_SUFFIX)) {
            continue;
        }


        if (asprintf(&str, "%s/%s", dir_path, file->d_name) == -1) {
            LOGMEM(NULL);
            return;
        }


        dlhandler = dlopen(str, RTLD_NOW);
        if (!dlhandler) {
            LOGERR(NULL, LY_ESYS, "Loading \"%s\" as a plugin failed (%s).", str, dlerror());
            free(str);
            continue;
        }
        if (ly_set_contains(&dlhandlers, dlhandler) != -1) {

            LOGVRB("Plugin \"%s\" already loaded.", str);
            free(str);


            dlclose(dlhandler);
            continue;
        }
        dlerror();


        name = strndup(file->d_name, len - LY_PLUGIN_SUFFIX_LEN);
        if (!name) {
            LOGMEM(NULL);
            dlclose(dlhandler);
            free(str);
            return;
        }

        if (ext_or_type) {
            ret = lyext_load_plugin(dlhandler, name);
        } else {
            ret = lytype_load_plugin(dlhandler, name);
        }
        if (!ret) {
            LOGVRB("Plugin \"%s\" successfully loaded.", str);

            ly_add_loaded_plugin(name);

            ly_set_add(&dlhandlers, dlhandler, LY_SET_OPT_USEASLIST);
        } else {
            free(name);
            dlclose(dlhandler);
        }
        free(str);

        if (ret == -1) {

            break;
        }
    }
}
