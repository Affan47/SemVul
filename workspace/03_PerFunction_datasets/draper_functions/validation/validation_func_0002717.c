fini (xlator_t *this)
{
        stripe_private_t      *priv = NULL;
        struct stripe_options *prev = NULL;
        struct stripe_options *trav = NULL;

        if (!this)
                goto out;

        priv = this->private;
        if (priv) {
                this->private = NULL;
                GF_FREE (priv->xl_array);

                trav = priv->pattern;
                while (trav) {
                        prev = trav;
                        trav = trav->next;
                        GF_FREE (prev);
                }
                GF_FREE (priv->last_event);
                LOCK_DESTROY (&priv->lock);
                GF_FREE (priv);
        }

out:
        return;
}
