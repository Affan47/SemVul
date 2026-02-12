xf86LoadModules(const char **list, void **optlist)
{
    int errmaj;
    void *opt;
    int i;
    char *name;
    Bool failed = FALSE;

    if (!list)
        return TRUE;

    for (i = 0; list[i] != NULL; i++) {


        name = xf86NormalizeName(list[i]);


        if (name == NULL || *name == '\0') {
            free(name);
            continue;
        }


        if (!xf86NameCmp(name, "keyboard")) {
            strcpy(name, "kbd");
        }

        if (optlist)
            opt = optlist[i];
        else
            opt = NULL;

        if (!LoadModule(name, opt, NULL, &errmaj)) {
            LoaderErrorMsg(NULL, name, errmaj, 0);
            failed = TRUE;
        }
        free(name);
    }
    return !failed;
}
