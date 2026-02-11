__qr_cache_prune (xlator_t *this)
{
        qr_private_t     *priv          = NULL;
        qr_conf_t        *conf          = NULL;
        qr_inode_table_t *table         = NULL;
        qr_inode_t        *curr         = NULL, *next = NULL;
        int32_t           index         = 0;
        uint64_t          size_to_prune = 0;
        uint64_t          size_pruned   = 0;

        GF_VALIDATE_OR_GOTO ("quick-read", this, out);
        priv = this->private;
        GF_VALIDATE_OR_GOTO (this->name, priv, out);

        table = &priv->table;
        conf = &priv->conf;

        size_to_prune = table->cache_used - conf->cache_size;

        for (index=0; index < conf->max_pri; index++) {
                list_for_each_entry_safe (curr, next, &table->lru[index], lru) {
                        size_pruned += curr->stbuf.ia_size;
                        inode_ctx_del (curr->inode, this, NULL);
                        __qr_inode_free (curr);
                        if (size_pruned >= size_to_prune)
                                goto done;
                }
        }

done:
        table->cache_used -= size_pruned;

out:
        return;
}
