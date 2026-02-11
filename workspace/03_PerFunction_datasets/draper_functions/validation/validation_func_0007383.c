remove_dup_colors(GBDATA *gb_item, const ad_item_selector *sel) {


    GBDATA   *gb_color = GB_entry(gb_item, AW_COLOR_GROUP_ENTRY);
    GB_ERROR  error    = NULL;

#if defined(DEBUG)
    int del_count = 0;
#endif

    if (gb_color) {
        GB_push_my_security(gb_color);
        while (!error) {
            GBDATA *gb_next_color = GB_nextEntry(gb_color);
            if (!gb_next_color) break;

            error = GB_delete(gb_next_color);
#if defined(DEBUG)
            if (!error) del_count++;
#endif
        }
        GB_pop_my_security(gb_color);
    }

#if defined(DEBUG)
    if (del_count) fprintf(stderr,
                           "- deleted %i duplicated '" AW_COLOR_GROUP_ENTRY "' from %s '%s'\n",
                           del_count,
                           sel->item_name,
                           sel->generate_item_id(GB_get_root(gb_item), gb_item));
#else
    sel = sel;
#endif

    return error;
}
