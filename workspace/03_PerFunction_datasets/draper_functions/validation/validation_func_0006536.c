gp_thread_start(gp_thread_creation_callback_t proc, void *proc_data,
                gp_thread_id *thread)
{
    gp_thread_creation_closure_t *closure =
        (gp_thread_creation_closure_t *)malloc(sizeof(*closure));
    pthread_t new_thread;
    pthread_attr_t attr;
    int code;

    if (!closure)
        return_error(gs_error_VMerror);
    closure->proc = proc;
    closure->proc_data = proc_data;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
    code = pthread_create(&new_thread, &attr, gp_thread_begin_wrapper,
                          closure);
    if (code) {
        *thread = NULL;
        free(closure);
        return_error(gs_error_ioerror);
    }
    *thread = (gp_thread_id)new_thread;
    return 0;
}
