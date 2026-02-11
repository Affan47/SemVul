globus_l_gfs_server_close_cb(
    globus_xio_server_t                 xio_server,
    void *                              user_arg)
{
    globus_gfs_embed_handle_t           handle;

    handle = (globus_gfs_embed_handle_t) user_arg;

    globus_mutex_lock(&handle->mutex);
    {
        handle->outstanding--;
        handle->xio_server = GLOBUS_NULL;
    }
    globus_mutex_unlock(&handle->mutex);

    if(handle->event_cb)
    {
        handle->event_cb(
            handle,
            GLOBUS_SUCCESS,
            GLOBUS_GFS_EMBED_EVENT_STOPPED,
            handle->event_arg);
    }
}
