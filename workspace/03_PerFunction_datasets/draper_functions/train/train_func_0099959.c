nufa_mknod (call_frame_t *frame, xlator_t *this,
            loc_t *loc, mode_t mode, dev_t rdev, mode_t umask, dict_t *params)
{
        dht_local_t *local = NULL;
        dht_conf_t  *conf  = NULL;
        xlator_t    *subvol = NULL;
        xlator_t    *avail_subvol = NULL;
        int          op_errno = -1;

        VALIDATE_OR_GOTO (frame, err);
        VALIDATE_OR_GOTO (this, err);
        VALIDATE_OR_GOTO (loc, err);

        conf  = this->private;

        dht_get_du_info (frame, this, loc);

        local = dht_local_init (frame, loc, NULL, GF_FOP_MKNOD);
        if (!local) {
                op_errno = ENOMEM;
                goto err;
        }

        subvol = dht_subvol_get_hashed (this, loc);
        if (!subvol) {
                gf_log (this->name, GF_LOG_DEBUG,
                        "no subvolume in layout for path=%s",
                        loc->path);
                op_errno = ENOENT;
                goto err;
        }


        avail_subvol = conf->private;
        if (dht_is_subvol_filled (this, (xlator_t *)conf->private)) {
                avail_subvol =
                        dht_free_disk_available_subvol (this,
                                                        (xlator_t *)conf->private,
                                                        local);
        }

        if (avail_subvol != subvol) {


                local->params = dict_ref (params);
                local->mode = mode;
                local->umask = umask;
                local->rdev = rdev;
                local->cached_subvol = avail_subvol;

                dht_linkfile_create (frame, nufa_mknod_linkfile_cbk,
                                     avail_subvol, subvol, loc);
                return 0;
        }

        gf_log (this->name, GF_LOG_TRACE,
                "creating %s on %s", loc->path, subvol->name);

        STACK_WIND_COOKIE (frame, dht_newfile_cbk, (void *)subvol, subvol,
                           subvol->fops->mknod, loc, mode, rdev, umask,
                           params);

        return 0;

err:
        op_errno = (op_errno == -1) ? errno : op_errno;
        DHT_STACK_UNWIND (mknod, frame, -1, op_errno,
                          NULL, NULL, NULL, NULL, NULL);

        return 0;
}
