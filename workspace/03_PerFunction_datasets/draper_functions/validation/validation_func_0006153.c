amsemaphore_new_with_value(int value) {
    amsemaphore_t *rval;

    if (!g_thread_supported())
        return NULL;

    rval = malloc(sizeof(*rval));
    rval->value = value;
    rval->mutex = g_mutex_new();
    rval->decrement_cond = g_cond_new();
    rval->zero_cond = g_cond_new();

    if (rval->mutex == NULL || rval->decrement_cond == NULL ||
        rval->zero_cond == NULL) {
        amsemaphore_free(rval);
        return NULL;
    } else {
        return rval;
    }
}
