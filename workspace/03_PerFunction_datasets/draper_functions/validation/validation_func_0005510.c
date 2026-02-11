context_item_realloc(jk_context_t *c, jk_context_item_t *ci)
{
    if (ci->size == ci->capacity) {
        char **uris;
        int capacity = ci->capacity + URI_INC_SIZE;

        uris = (char **)jk_pool_alloc(&c->p, sizeof(char *) * capacity);

        if (!uris)
            return JK_FALSE;

        memcpy(uris, ci->uris, sizeof(char *) * ci->capacity);

        ci->uris = uris;
        ci->capacity = capacity;
    }

    return JK_TRUE;
}
