EXPORTED void clearentryatt(struct entryattlist **l, const char *entry,
                   const char *attrib)
{
    struct entryattlist *ea, **pea;
    struct attvaluelist *av, **pav;

    for (pea = l ; *pea ; pea = &(*pea)->next) {
        if (!strcmp((*pea)->entry, entry))
            break;
    }
    ea = *pea;
    if (!ea)
        return;

    for (pav = &(*pea)->attvalues ; *pav ; pav = &(*pav)->next) {
        if (!strcmp((*pav)->attrib, attrib))
            break;
    }
    av = *pav;
    if (!av)
        return;


    *pav = av->next;
    free(av->attrib);
    buf_free(&av->value);
    free(av);

    if (!ea->attvalues) {

        *pea = ea->next;
        free(ea->entry);
        free(ea);
    }
}
