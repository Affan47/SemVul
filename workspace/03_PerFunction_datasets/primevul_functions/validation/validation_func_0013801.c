void gp_workers_free(struct gp_workers *w)
{
    struct gp_thread *t;
    void *retval;


    pthread_mutex_lock(&w->lock);

    w->shutdown = true;


    pthread_mutex_unlock(&w->lock);


    while (w->free_list) {

        t = w->free_list;
        LIST_DEL(w->free_list, t);


        pthread_mutex_lock(&t->cond_mutex);
        pthread_cond_signal(&t->cond_wakeup);

        pthread_mutex_unlock(&t->cond_mutex);

        pthread_join(t->tid, &retval);

        pthread_mutex_destroy(&t->cond_mutex);
        pthread_cond_destroy(&t->cond_wakeup);
        free(t);
    }


    while (w->busy_list) {

        t = w->busy_list;
        LIST_DEL(w->free_list, t);


        pthread_mutex_lock(&t->cond_mutex);
        pthread_cond_signal(&t->cond_wakeup);

        pthread_mutex_unlock(&t->cond_mutex);

        pthread_join(t->tid, &retval);

        pthread_mutex_destroy(&t->cond_mutex);
        pthread_cond_destroy(&t->cond_wakeup);
        free(t);
    }

    close(w->sig_pipe[0]);
    close(w->sig_pipe[1]);

    pthread_mutex_destroy(&w->lock);

    free(w);
}
