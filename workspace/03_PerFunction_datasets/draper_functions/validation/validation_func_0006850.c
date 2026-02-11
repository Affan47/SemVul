globus_l_gfs_data_write_eof_cb(
    void *                              user_arg,
    globus_ftp_control_handle_t *       handle,
    globus_object_t *                   error,
    globus_byte_t *                     buffer,
    globus_size_t                       length,
    globus_off_t                        offset,
    globus_bool_t                       eof)
{
    globus_bool_t                       end = GLOBUS_FALSE;
    globus_result_t                     result;
    globus_l_gfs_data_operation_t *     op;
    GlobusGFSName(globus_l_gfs_data_write_eof_cb);
    GlobusGFSDebugEnter();

    op = (globus_l_gfs_data_operation_t *) user_arg;

    GlobusGFSDebugState(op->state);
    GlobusGFSDebugState(op->data_handle->state);
    if(error != NULL)
    {


        op->cached_res = globus_error_put(globus_object_copy(error));
        globus_gfs_log_result(
            GLOBUS_GFS_LOG_WARN, "write_eof_cb error", op->cached_res);
        globus_l_gfs_data_cb_error(op->data_handle);
        end = GLOBUS_TRUE;
    }
    else
    {
        globus_mutex_lock(&op->session_handle->mutex);
        {
            switch(op->data_handle->state)
            {
                case GLOBUS_L_GFS_DATA_HANDLE_INUSE:

                if(op->data_handle->info.mode == 'E')
                {
                    result = globus_ftp_control_data_send_eof(
                        &op->data_handle->data_channel,
                        op->eof_count,
                        op->stripe_count,
                        (op->node_ndx == 0 || op->stripe_count == 1) ?
                            GLOBUS_TRUE : GLOBUS_FALSE,
                        globus_l_gfs_data_send_eof_cb,
                        op);
                    if(op->node_ndx != 0 && op->stripe_count > 1)
                    {


                        globus_gfs_event_info_t        event_reply;
                        memset(&event_reply, '\0',
                            sizeof(globus_gfs_event_info_t));
                        event_reply.id = op->id;
                        event_reply.eof_count = op->eof_count;
                        event_reply.type = GLOBUS_GFS_EVENT_PARTIAL_EOF_COUNT;
                        event_reply.node_count = op->node_count;
                        if(op->event_callback != NULL)
                        {
                                op->event_callback(
                                &event_reply,
                                op->user_arg);
                        }
                        else
                        {
                            globus_gfs_ipc_reply_event(
                                op->ipc_handle,
                                &event_reply);
                        }
                        op->sent_partial_eof++;
                    }
                    if(result != GLOBUS_SUCCESS)
                    {
                        globus_gfs_log_result(
                            GLOBUS_GFS_LOG_WARN, "ERROR", result);
                        op->cached_res = result;
                        end = GLOBUS_TRUE;
                    }
                }
                else
                {
                    op->data_handle->state = GLOBUS_L_GFS_DATA_HANDLE_CLOSING;
                    result = globus_ftp_control_data_force_close(
                        &op->data_handle->data_channel,
                        globus_l_gfs_data_finish_fc_cb,
                        op);
                    if(result != GLOBUS_SUCCESS)
                    {
                        op->data_handle->state =
                            GLOBUS_L_GFS_DATA_HANDLE_TE_PRE_CLOSED;
                        end = GLOBUS_TRUE;
                    }
                }

                default:
                    break;
            }
        }
        globus_mutex_unlock(&op->session_handle->mutex);
    }

    if(end)
    {
        globus_l_gfs_data_end_transfer_kickout(op);
    }

    GlobusGFSDebugExit();
}
