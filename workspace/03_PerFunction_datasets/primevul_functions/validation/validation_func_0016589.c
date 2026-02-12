ly_clean_plugins(void)
{
    FUN_IN;

    unsigned int u;
    int ret = EXIT_SUCCESS;

#ifdef STATIC

    pthread_mutex_lock(&plugins_lock);

    if(ext_plugins) {
        free(ext_plugins);
        ext_plugins = NULL;
        ext_plugins_count = 0;
    }

    if(type_plugins) {
        free(type_plugins);
        type_plugins = NULL;
        type_plugins_count = 0;
    }

    for (u = 0; u < loaded_plugins_count; ++u) {
        free(loaded_plugins[u]);
    }
    free(loaded_plugins);
    loaded_plugins = NULL;
    loaded_plugins_count = 0;


    pthread_mutex_unlock(&plugins_lock);
    return ret;
#endif


    pthread_mutex_lock(&plugins_lock);

    if (--plugin_refs) {

        ret = EXIT_FAILURE;
        goto cleanup;
    }

    if (!ext_plugins_count && !type_plugins_count) {

        goto cleanup;
    }


    free(ext_plugins);
    ext_plugins = NULL;
    ext_plugins_count = 0;

    free(type_plugins);
    type_plugins = NULL;
    type_plugins_count = 0;

    for (u = 0; u < loaded_plugins_count; ++u) {
        free(loaded_plugins[u]);
    }
    free(loaded_plugins);
    loaded_plugins = NULL;
    loaded_plugins_count = 0;


    for (u = 0; u < dlhandlers.number; u++) {
        dlclose(dlhandlers.set.g[u]);
    }
    free(dlhandlers.set.g);
    dlhandlers.set.g = NULL;
    dlhandlers.size = 0;
    dlhandlers.number = 0;

cleanup:

    pthread_mutex_unlock(&plugins_lock);

    return ret;
}
