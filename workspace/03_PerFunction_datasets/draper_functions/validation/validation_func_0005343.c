notify (xlator_t *this, int32_t event, void *data, ...)
{
        int32_t             ret     = 0;
        fuse_private_t     *private = NULL;
        glusterfs_graph_t  *graph = NULL;

        private = this->private;

        graph = data;

        gf_log ("fuse", GF_LOG_DEBUG, "got event %d on graph %d",
                event, ((graph) ? graph->id : 0));

        switch (event)
        {
        case GF_EVENT_GRAPH_NEW:
                break;

        case GF_EVENT_CHILD_UP:
        case GF_EVENT_CHILD_DOWN:
        case GF_EVENT_CHILD_CONNECTING:
        {
                if (graph) {
                        ret = fuse_graph_setup (this, graph);
                        if (ret)
                                gf_log (this->name, GF_LOG_WARNING,
                                        "failed to setup the graph");
                }

                if ((event == GF_EVENT_CHILD_UP)
                    || (event == GF_EVENT_CHILD_DOWN)) {
                        pthread_mutex_lock (&private->sync_mutex);
                        {
                                private->event_recvd = 1;
                                pthread_cond_broadcast (&private->sync_cond);
                        }
                        pthread_mutex_unlock (&private->sync_mutex);
                }

                if (!private->fuse_thread_started) {
                        private->fuse_thread_started = 1;

                        ret = pthread_create (&private->fuse_thread, NULL,
                                              fuse_thread_proc, this);
                        if (ret != 0) {
                                gf_log (this->name, GF_LOG_DEBUG,
                                        "pthread_create() failed (%s)",
                                        strerror (errno));
                                break;
                        }
                }

                break;
        }

        default:
                break;
        }

        return ret;
}
