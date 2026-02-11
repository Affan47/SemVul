prot_free(Repl_Protocol **rpp)
{
    Repl_Protocol *rp = NULL;

    if (rpp == NULL || *rpp == NULL) return;

    rp = *rpp;

    PR_Lock(rp->lock);
    if (NULL != rp->prp_incremental)
    {
        rp->prp_incremental->delete(&rp->prp_incremental);
    }
    if (NULL != rp->prp_total)
    {
        rp->prp_total->delete(&rp->prp_total);
    }
    if (NULL != rp->replica_object)
    {
        object_release(rp->replica_object);
    }
    if ((NULL != rp->conn) && (NULL != rp->delete_conn))
    {
        rp->delete_conn(rp->conn);
        rp->conn = NULL;
    }
    rp->prp_active_protocol = NULL;
    PR_Unlock(rp->lock);
    PR_DestroyLock(rp->lock);
    slapi_ch_free((void **)rpp);
}
