dht_layout_set (xlator_t *this, inode_t *inode, dht_layout_t *layout)
{
        dht_conf_t   *conf = NULL;
        int           oldret = -1;
        int           ret = 0;
        dht_layout_t *old_layout;
        uint64_t      old_layout_int;

        conf = this->private;
        if (!conf)
                goto out;

        LOCK (&conf->layout_lock);
        {
                oldret = inode_ctx_get (inode, this, &old_layout_int);

                layout->ref++;
                ret = inode_ctx_put (inode, this, (uint64_t) (unsigned long)
                                     layout);
        }
        UNLOCK (&conf->layout_lock);

        if (oldret == 0) {
                old_layout = (dht_layout_t *) (unsigned long) old_layout_int;
                dht_layout_unref (this, old_layout);
        }

out:
        return ret;
}
