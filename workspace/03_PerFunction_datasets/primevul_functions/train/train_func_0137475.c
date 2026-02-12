static gboolean on_client_data_in(GIOChannel* ch, GIOCondition cond, gpointer user_data)
{
    char *line;
    gsize len;
    GIOStatus st;
    const char* md5;
    Cache* cache;
    GFile* gf;
    gboolean ret = TRUE;

    if(cond & (G_IO_HUP|G_IO_ERR) )
    {
        on_client_closed(user_data);
        return FALSE;
    }

retry:
    st = g_io_channel_read_line( ch, &line, &len, NULL, NULL );
    if( st == G_IO_STATUS_AGAIN )
        goto retry;
    if( st != G_IO_STATUS_NORMAL ) {
        on_client_closed(user_data);
        return FALSE;
    }

    --len;
    line[len] = 0;

    DEBUG("line(%d) = %s", (int)len, line);

    if( memcmp(line, "REG:", 4) == 0 )
    {
        int n_files = 0, i;
        char *pline = line + 4;
        char *sep, *menu_name, *lang_name, *cache_dir;
        char **files = NULL;
        char **env;
        char reload_cmd[38] = "REL:";

        len -= 4;


        md5 = pline + len - 32;

        cache = (Cache*)g_hash_table_lookup(hash, md5);
        if( !cache )
        {
            sep = strchr(pline, '\t');
            *sep = '\0';
            menu_name = pline;
            pline = sep + 1;

            sep = strchr(pline, '\t');
            *sep = '\0';
            lang_name = pline;
            pline = sep + 1;

            ((char *)md5)[-1] = '\0';
            env = g_strsplit(pline, "\t", 0);

            cache_dir = env[0];


            cache = g_slice_new0( Cache );
            cache->cache_file = g_build_filename(*cache_dir ? cache_dir : g_get_user_cache_dir(), "menus", md5, NULL );
            if( ! cache_file_is_updated(cache->cache_file, &n_files, &files) )
            {

                if(! regenerate_cache( menu_name, lang_name, cache->cache_file, env, &n_files, &files ) )
                {
                    DEBUG("regeneration of cache failed!!");
                }
            }
            else
            {

                cache->need_reload = TRUE;
                cache->delayed_reload_handler = g_timeout_add_seconds_full(G_PRIORITY_LOW, 3,
                                                    (GSourceFunc)delayed_reload, cache, NULL);
            }
            memcpy( cache->md5, md5, 33 );
            cache->n_files = n_files;
            cache->files = files;
            cache->menu_name = g_strdup(menu_name);
            cache->lang_name = g_strdup(lang_name);
            cache->env = env;
            cache->mons = g_new0(GFileMonitor*, n_files+1);

            DEBUG("%d files/dirs are monitored.", n_files);
            for( i = 0; i < n_files; ++i )
            {
                gf = g_file_new_for_path( files[i] + 1 );
                if( files[i][0] == 'D' )
                    cache->mons[i] = g_file_monitor_directory( gf, 0, NULL, NULL );
                else
                    cache->mons[i] = g_file_monitor_file( gf, 0, NULL, NULL );
                DEBUG("monitor: %s", g_file_get_path(gf));
                g_signal_connect(cache->mons[i], "changed",
                                 G_CALLBACK(on_file_changed), cache);
                g_object_unref(gf);
            }


            g_hash_table_insert(hash, cache->md5, cache);
            DEBUG("new menu cache %p added to hash", cache);
        }
        else if (access(cache->cache_file, R_OK) != 0)
        {

            if (!regenerate_cache(cache->menu_name, cache->lang_name, cache->cache_file,
                                  cache->env, &cache->n_files, &cache->files))
            {
                DEBUG("regeneration of cache failed.");
            }
        }

        cache->clients = g_slist_prepend(cache->clients, user_data);
        if(cache->delayed_free_handler)
        {
            g_source_remove(cache->delayed_free_handler);
            cache->delayed_free_handler = 0;
        }
        DEBUG("client %p added to cache %p", ch, cache);


        DEBUG("fake reload!");
        memcpy(reload_cmd + 4, md5, 32);

        reload_cmd[36] = '\n';
        reload_cmd[37] = '\0';

        DEBUG("reload command: %s", reload_cmd);
        ret = write(g_io_channel_unix_get_fd(ch), reload_cmd, 37) > 0;
    }
    else if( memcmp(line, "UNR:", 4) == 0 )
    {
        md5 = line + 4;
        DEBUG("unregister: %s", md5);
        cache = (Cache*)g_hash_table_lookup(hash, md5);
        if(cache && cache->clients)
        {

            cache->clients = g_slist_remove(cache->clients, user_data);
            if(cache->clients == NULL)
                cache_free(cache);
        }
        else
            DEBUG("bug! client is not found.");
    }
    g_free( line );

    return ret;
}
