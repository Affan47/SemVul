knowledge_alchemy_detail(const char *value, StringBuffer *buf) {
    const recipe *rec = knowledge_alchemy_get_recipe(value);
    const linked_char *next;
    const archetype *arch;
    char name[MAX_BUF];


    if (!rec)

        return;

    arch = find_archetype(rec->arch_name[RANDOM()%rec->arch_names]);
    if (!arch)

        return;

    if (strcmp(rec->title, "NONE"))
        stringbuffer_append_printf(buf, "The %s of %s", arch->clone.name, rec->title);
    else {
        if (arch->clone.title != NULL) {
            stringbuffer_append_printf(buf, "The %s %s", arch->clone.name, arch->clone.title);
        }
        else
            stringbuffer_append_printf(buf, "The %s", arch->clone.name);
    }

    arch = find_archetype(rec->cauldron);
    if (arch)
        query_name(&arch->clone, name, MAX_BUF);
    else
        snprintf(name, sizeof(name), "an unknown place");

    stringbuffer_append_printf(buf, " is made at %s and uses the following ingredients:", name);

    for (next = rec->ingred; next != NULL; next = next->next) {
        stringbuffer_append_printf(buf, "\n - %s", next->name);
    }

}
