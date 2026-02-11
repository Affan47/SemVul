xcalloc(size_t nmemb, size_t size) {
    void *p;

    if (size == 0 || nmemb == 0)
        return NULL;

    if (!(p = calloc(nmemb, size)))
        oom();

    return p;
}
