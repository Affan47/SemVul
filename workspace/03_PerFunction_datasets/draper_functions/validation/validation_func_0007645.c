globus_l_gfs_operation_finished_kickout(
    void *                              user_arg)
{
    globus_bool_t                       destroy_session = GLOBUS_FALSE;
    globus_bool_t                       destroy_op = GLOBUS_FALSE;
    globus_l_gfs_data_bounce_t *        bounce;
    void *                              remote_data_arg = NULL;
    globus_l_gfs_data_operation_t *     op;
    GlobusGFSName(globus_l_gfs_operation_finished_kickout);
    GlobusGFSDebugEnter();

    bounce = (globus_l_gfs_data_bounce_t *) user_arg;
    op = bounce->op;

    if(op->callback != NULL)
    {
        op->callback(
            bounce->finished_info,
            op->user_arg);
    }
    else
    {
        if(bounce->finished_info->type == GLOBUS_GFS_OP_SESSION_START)
        {
            globus_gfs_ipc_reply_session(
                op->ipc_handle,
                bounce->finished_info);
        }
        else
        {
            globus_gfs_ipc_reply_finished(
                op->ipc_handle,
                bounce->finished_info);
        }
    }
    globus_l_gfs_data_reset_watchdog(op->session_handle, NULL);

    globus_mutex_lock(&op->session_handle->mutex);
    {
        GFSDataOpDec(op, destroy_op, destroy_session);
        if(destroy_op)
        {
            remote_data_arg = globus_l_gfs_data_check(
                op->session_handle, op->data_handle);
        }
    }
    globus_mutex_unlock(&op->session_handle->mutex);


    if(destroy_op)
    {
        globus_l_gfs_data_fire_cb(op, remote_data_arg, destroy_session);
        globus_l_gfs_data_operation_destroy(op);
    }

    if(bounce->finished_info->op_info)
    {
        globus_free(bounce->finished_info->op_info);
        bounce->finished_info->op_info = NULL;
    }
    globus_free(bounce);

    GlobusGFSDebugExit();
}
