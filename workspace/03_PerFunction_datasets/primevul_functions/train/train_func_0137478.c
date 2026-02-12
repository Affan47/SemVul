static gpointer menu_cache_loader_thread(gpointer data)
{
    MenuCache* cache = (MenuCache*)data;


    if(!connect_server(cache->cancellable))
    {
        g_print("unable to connect to menu-cached.\n");
        SET_CACHE_READY(cache);
        return NULL;
    }

    if ((cache->cancellable && g_cancellable_is_cancelled(cache->cancellable)) ||
        !register_menu_to_server(cache))
        SET_CACHE_READY(cache);
    return NULL;
}
