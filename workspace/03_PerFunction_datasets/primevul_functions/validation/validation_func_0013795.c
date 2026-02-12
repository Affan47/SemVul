static void gp_query_assign(struct gp_workers *w, struct gp_query *q)
{
    struct gp_thread *t = NULL;


    pthread_mutex_lock(&w->lock);
    if (w->free_list) {
        t = w->free_list;
        LIST_DEL(w->free_list, t);
        LIST_ADD(w->busy_list, t);
    }

    pthread_mutex_unlock(&w->lock);

    if (t) {


        pthread_mutex_lock(&t->cond_mutex);


        t->query = q;
        pthread_cond_signal(&t->cond_wakeup);


        pthread_mutex_unlock(&t->cond_mutex);

    } else {


        q->next = w->wait_list;
        w->wait_list = q;
    }
}
