request_find(struct fuse_pqueue *fpq, u64 unique)
{
	struct fuse_req *req;

	list_for_each_entry(req, &fpq->processing, list) {
		if (req->in.h.unique == unique || req->intr_unique == unique)
			return req;
	}
	return NULL;
}
