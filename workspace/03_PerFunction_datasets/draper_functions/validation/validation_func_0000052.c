clnt_fd_lk_local_ref (xlator_t *this, clnt_fd_lk_local_t *local)
{
        GF_VALIDATE_OR_GOTO (this->name, local, out);

        LOCK (&local->lock);
        {
                local->ref++;
        }
        UNLOCK (&local->lock);
out:
        return local;
}
