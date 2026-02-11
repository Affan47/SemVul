pump_cmd_start_getxattr_cbk (call_frame_t *frame,
                             void *cookie,
                             xlator_t *this,
                             int32_t op_ret,
                             int32_t op_errno,
                             dict_t *dict)
{
        afr_local_t *local = NULL;
        char *path = NULL;

        pump_state_t state;
        int ret = 0;
        int need_unwind = 0;
        int dict_ret = -1;

        local = frame->local;

        if (op_ret < 0) {
                gf_log (this->name, GF_LOG_DEBUG,
                        "getxattr failed - changing pump "
                        "state to RUNNING with '/'");
                path = "/";
                ret = op_ret;
        } else {
                gf_log (this->name, GF_LOG_TRACE,
                        "getxattr succeeded");

                dict_ret =  dict_get_str (dict, PUMP_PATH, &path);
                if (dict_ret < 0)
                        path = "/";
        }

        state = pump_get_state ();
        if ((state == PUMP_STATE_RUNNING) ||
            (state == PUMP_STATE_RESUME)) {
                gf_log (this->name, GF_LOG_ERROR,
                        "Pump is already started");
                ret = -1;
                goto out;
        }

        pump_set_resume_path (this, path);

        if (is_pump_aborted (this))

                ret = pump_initiate_sink_connect (frame, this);
        else {


                gf_log (this->name, GF_LOG_DEBUG,
                        "about to start synctask");
                ret = pump_start_synctask (this);
                need_unwind = 1;
        }

out:
        if ((ret < 0) || (need_unwind == 1)) {
                local->op_ret = ret;
                pump_command_reply (frame, this);
        }
	return 0;
}
