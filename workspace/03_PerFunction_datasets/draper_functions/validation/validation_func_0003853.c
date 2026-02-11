bd_get_titles(BLURAY *bd, uint8_t flags, uint32_t min_title_length)
{
    if (!bd) {
        BD_DEBUG(DBG_BLURAY | DBG_CRIT, "bd_get_titles(NULL) failed\n");
        return 0;
    }

    if (bd->title_list != NULL) {
        nav_free_title_list(bd->title_list);
    }
    bd->title_list = nav_get_title_list(bd->device_path, flags, min_title_length);

    if (!bd->title_list) {
        BD_DEBUG(DBG_BLURAY | DBG_CRIT, "nav_get_title_list(%s) failed\n", bd->device_path);
        return 0;
    }


    if (bd->libbdplus) {
        libbdplus_event(bd->libbdplus, 0xffffffff, bd->index->num_titles, 0);
    }

    return bd->title_list->count;
}
