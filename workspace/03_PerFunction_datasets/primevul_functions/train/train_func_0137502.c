void on_file_changed( GFileMonitor* mon, GFile* gf, GFile* other,
                      GFileMonitorEvent evt, Cache* cache )
{
#ifdef G_ENABLE_DEBUG
    char *path = g_file_get_path(gf);
    g_debug("file %s is changed (%d).", path, evt);
    g_free(path);
#endif

    {


        int idx;

        for(idx = 0; idx < cache->n_files; ++idx)
        {
            if(mon == cache->mons[idx])
                break;
        }

        if( G_LIKELY(idx < cache->n_files) && cache->files[idx][0] == 'D' )
        {
            char* changed_file = g_file_get_path(gf);
            char* dir_path = cache->files[idx]+1;
            int len = strlen(dir_path);

            if( strncmp(changed_file, dir_path, len) == 0 && changed_file[len] == '/' )
            {
                char* base_name = changed_file + len + 1;
                gboolean skip = TRUE;

                if( g_str_has_suffix(base_name, ".desktop") )
                {
                        skip = FALSE;
                }
                else if( g_str_has_suffix(base_name, ".directory") )
                    skip = FALSE;

                if( skip )
                {
                    DEBUG("files are changed, but no re-generation is needed.");
                    return;
                }
            }
            g_free(changed_file);
        }
    }

    if( cache->delayed_reload_handler )
    {

        cache->need_reload = TRUE;
        g_source_remove(cache->delayed_reload_handler);
    }
    else
    {


        cache->need_reload = TRUE;
        do_reload(cache);
    }

    cache->delayed_reload_handler = g_timeout_add_seconds_full( G_PRIORITY_LOW, 3, (GSourceFunc)delayed_reload, cache, NULL );
}
