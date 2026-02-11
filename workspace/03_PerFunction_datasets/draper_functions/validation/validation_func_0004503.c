get_typedata_by_name(const char *name) {
    int i;

    for (i = 0; i < item_types_size; i++)
        if (!strcmp(item_types[i].name, name))
            return &item_types[i];
    for (i = 0; i < item_types_size; i++)
        if (!strcmp(item_types[i].name_pl, name)) {
            LOG(llevInfo, "get_typedata_by_name: I have been sent the plural %s, the singular form %s is preffered\n", name, item_types[i].name);
            return &item_types[i];
        }
    return NULL;
}
