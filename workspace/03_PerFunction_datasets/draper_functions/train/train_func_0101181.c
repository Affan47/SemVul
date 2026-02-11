arglist_remove_flag(list_t *list, const char *name)
{
    listitem_t *i = arglist_find(list, name);
    if (i) {
        list_remove(list, i);
        return 1;
    }
    return 0;
}
