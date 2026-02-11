freeserver(struct server *a) {
    if (a->group_pcre) pcre_free(a->group_pcre);
    if (a->name) free(a->name);
    if (a->username) free(a->username);
    if (a->password) free(a->password);
    free(a);
}
