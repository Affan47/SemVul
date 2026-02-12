static void gp_handle_reply(verto_ctx *vctx, verto_ev *ev)
{
    struct gp_workers *w;
    struct gp_query *q = NULL;
    char dummy;
    int ret;

    w = verto_get_private(ev);


    ret = read(w->sig_pipe[0], &dummy, 1);
    if (ret) {

    }


    if (w->reply_list) {

        pthread_mutex_lock(&w->lock);

        if (w->reply_list != NULL) {
            q = w->reply_list;
            w->reply_list = q->next;
        }


        pthread_mutex_unlock(&w->lock);
    }

    if (q) {
        switch (q->status) {
        case GP_QUERY_IN:

        case GP_QUERY_ERR:
            GPDEBUGN(3, "[status] Handling query error, terminating CID %d.\n",
                     gp_conn_get_cid(q->conn));
            gp_conn_free(q->conn);
            gp_query_free(q, true);
            break;

        case GP_QUERY_OUT:
            GPDEBUGN(3, "[status] Handling query reply: %p (%zu)\n", q->buffer, q->buflen);
            gp_socket_send_data(vctx, q->conn, q->buffer, q->buflen);
            gp_query_free(q, false);
            break;
        }
    }


    q = NULL;

    if (w->wait_list) {


        if (w->wait_list) {
            q = w->wait_list;
            w->wait_list = q->next;
            q->next = NULL;
        }
    }

    if (q) {
        gp_query_assign(w, q);
    }
}
