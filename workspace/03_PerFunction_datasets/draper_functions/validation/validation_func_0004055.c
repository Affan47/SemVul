stripe_setattr (call_frame_t *frame, xlator_t *this, loc_t *loc,
                struct iatt *stbuf, int32_t valid, dict_t *xdata)
{
        xlator_list_t    *trav = NULL;
        stripe_local_t   *local = NULL;
        stripe_private_t *priv = NULL;
        int32_t           op_errno = EINVAL;

        VALIDATE_OR_GOTO (frame, err);
        VALIDATE_OR_GOTO (this, err);
        VALIDATE_OR_GOTO (loc, err);
        VALIDATE_OR_GOTO (loc->path, err);
        VALIDATE_OR_GOTO (loc->inode, err);

        priv = this->private;
        trav = this->children;

        if (priv->first_child_down) {
                op_errno = ENOTCONN;
                goto err;
        }


        local = mem_get0 (this->local_pool);
        if (!local) {
                op_errno = ENOMEM;
                goto err;
        }
        local->op_ret = -1;
        frame->local = local;
        if (!IA_ISDIR (loc->inode->ia_type) &&
            !IA_ISREG (loc->inode->ia_type)) {
                local->call_count = 1;
                STACK_WIND (frame, stripe_setattr_cbk, FIRST_CHILD (this),
                            FIRST_CHILD (this)->fops->setattr,
                            loc, stbuf, valid, NULL);
                return 0;
        }

        local->call_count = priv->child_count;
        while (trav) {
                STACK_WIND (frame, stripe_setattr_cbk,
                            trav->xlator, trav->xlator->fops->setattr,
                            loc, stbuf, valid, NULL);
                trav = trav->next;
        }

        return 0;
err:
        STRIPE_STACK_UNWIND (setattr, frame, -1, op_errno, NULL, NULL, NULL);
        return 0;
}
