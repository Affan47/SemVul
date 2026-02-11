do_user_quota(struct sync_name_list *master_quotaroots,
			 struct sync_quota_list *replica_quota)
{
    int r;
    struct sync_name *mitem;
    struct sync_quota *rquota;
    struct quota q;


    for (mitem = master_quotaroots->head; mitem; mitem = mitem->next) {
	rquota = sync_quota_lookup(replica_quota, mitem->name);
	q.root = mitem->name;
	if (rquota)
	    rquota->done = 1;
	r = update_quota_work(&q, rquota);
	if (r) return r;
    }


    for (rquota = replica_quota->head; rquota; rquota = rquota->next) {
	if (rquota->done) continue;
	r = delete_quota(rquota->root);
	if (r) return r;
    }

    return 0;
}
