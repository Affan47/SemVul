get_domain (pl_inode_t *pl_inode, const char *volume)
{
        pl_dom_list_t *dom = NULL;

        GF_VALIDATE_OR_GOTO (POSIX_LOCKS, pl_inode, out);
        GF_VALIDATE_OR_GOTO (POSIX_LOCKS, volume, out);

        pthread_mutex_lock (&pl_inode->mutex);
        {
                list_for_each_entry (dom, &pl_inode->dom_list, inode_list) {
                        if (strcmp (dom->domain, volume) == 0)
                                goto unlock;
                }

                dom = __allocate_domain (volume);
                if (dom)
                        list_add (&dom->inode_list, &pl_inode->dom_list);
        }
unlock:
        pthread_mutex_unlock (&pl_inode->mutex);
        if (dom) {
                gf_log (POSIX_LOCKS, GF_LOG_TRACE, "Domain %s found", volume);
        } else {
                gf_log (POSIX_LOCKS, GF_LOG_TRACE, "Domain %s not found", volume);
        }
out:
        return dom;
}
