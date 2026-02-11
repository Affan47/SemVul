dht_vgetxattr_cbk (call_frame_t *frame, void *cookie, xlator_t *this,
                   int op_ret, int op_errno, dict_t *xattr, dict_t *xdata)
{
        dht_local_t  *local         = NULL;
        int           ret           = 0;
        dict_t       *dict          = NULL;
        call_frame_t *prev          = NULL;
        gf_boolean_t  flag          = _gf_true;

        local = frame->local;
        prev = cookie;

        if (op_ret < 0) {
                local->op_ret = -1;
                local->op_errno = op_errno;
                gf_log (this->name, GF_LOG_ERROR, "Subvolume %s returned -1 "
                        "(%s)", prev->this->name, strerror (op_errno));
                goto unwind;
        }

        ret = dht_vgetxattr_alloc_and_fill (local, xattr, this,
                                            op_errno);
        if (ret) {
                gf_log (this->name, GF_LOG_ERROR,
                        "alloc or fill failure");
                goto unwind;
        }

        flag = (local->layout->cnt > 1) ? _gf_true : _gf_false;

        ret = dht_vgetxattr_fill_and_set (local, &dict, this, flag);
        if (ret)
                goto unwind;

        DHT_STACK_UNWIND (getxattr, frame, 0, 0, dict, xdata);
        goto cleanup;

 unwind:
        DHT_STACK_UNWIND (getxattr, frame, -1, local->op_errno,
                          NULL, NULL);
 cleanup:
        if (dict)
                dict_unref (dict);

        return 0;
}
