dht_rmdir_is_subvol_empty (call_frame_t *frame, xlator_t *this,
                           gf_dirent_t *entries, xlator_t *src)
{
        int                 ret = 0;
        int                 build_ret = 0;
        gf_dirent_t        *trav = NULL;
        call_frame_t       *lookup_frame = NULL;
        dht_local_t        *lookup_local = NULL;
        dht_local_t        *local = NULL;

        local = frame->local;

        list_for_each_entry (trav, &entries->list, list) {
                if (strcmp (trav->d_name, ".") == 0)
                        continue;
                if (strcmp (trav->d_name, "..") == 0)
                        continue;
                if (check_is_linkfile (NULL, (&trav->d_stat), NULL) == 1) {
                        ret++;
                        continue;
                }


                return 0;
        }

        list_for_each_entry (trav, &entries->list, list) {
                if (strcmp (trav->d_name, ".") == 0)
                        continue;
                if (strcmp (trav->d_name, "..") == 0)
                        continue;

                lookup_frame = NULL;
                lookup_local = NULL;

                lookup_frame = copy_frame (frame);
                if (!lookup_frame) {


                        goto err;
                }

                lookup_local = GF_CALLOC (sizeof (*local), 1,
                                          gf_dht_mt_dht_local_t);
                if (!lookup_local) {
                        goto err;
                }

                lookup_frame->local = lookup_local;
                lookup_local->main_frame = frame;

                build_ret = dht_build_child_loc (this, &lookup_local->loc,
                                                 &local->loc, trav->d_name);
                if (build_ret != 0)
                        goto err;

                uuid_copy (lookup_local->loc.gfid, trav->d_stat.ia_gfid);

                gf_log (this->name, GF_LOG_TRACE,
                        "looking up %s on %s",
                        lookup_local->loc.path, src->name);

                LOCK (&frame->lock);
                {
                        local->call_cnt++;
                }
                UNLOCK (&frame->lock);

                STACK_WIND (lookup_frame, dht_rmdir_lookup_cbk,
                            src, src->fops->lookup,
                            &lookup_local->loc, NULL);
                ret++;
        }

        return ret;
err:
        DHT_STACK_DESTROY (lookup_frame);
        return 0;
}
