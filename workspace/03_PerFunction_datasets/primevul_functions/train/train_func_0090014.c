static struct fuse_context_i *fuse_get_context_internal(void)
{
    struct fuse_context_i *c;

    c = (struct fuse_context_i *) pthread_getspecific(fuse_context_key);
    if (c == NULL) {
        c = (struct fuse_context_i *) malloc(sizeof(struct fuse_context_i));
        if (c == NULL) {


            fprintf(stderr, "fuse: failed to allocate thread specific data\n");
            abort();
        }
        pthread_setspecific(fuse_context_key, c);
    }
    return c;
}
