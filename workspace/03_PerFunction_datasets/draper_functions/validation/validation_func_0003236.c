url_free(struct url u) {
    if (u.host != NULL) {
        free(u.host);
        u.host = NULL;
    }
    if (u.proto != NULL) {
        free(u.proto);
        u.proto = NULL;
    }
    if (u.path != NULL) {
        free(u.path);
        u.path = NULL;
    }
    if (u.para != NULL) {
        free(u.path);
        u.path = NULL;
    }
}
