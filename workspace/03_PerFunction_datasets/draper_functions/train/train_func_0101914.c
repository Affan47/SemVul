__wb_request_unref (wb_request_t *req)
{
        int         ret = -1;
	wb_inode_t *wb_inode = NULL;

	wb_inode = req->wb_inode;

        if (req->refcount <= 0) {
                gf_log ("wb-request", GF_LOG_WARNING,
                        "refcount(%d) is <= 0", req->refcount);
                goto out;
        }

        ret = --req->refcount;
        if (req->refcount == 0) {
                list_del_init (&req->todo);
                list_del_init (&req->lie);
		list_del_init (&req->wip);

		list_del_init (&req->all);
		if (list_empty (&wb_inode->all)) {
			wb_inode->gen = 0;

			wb_inode->window_current = 0;
		}

		list_del_init (&req->winds);
		list_del_init (&req->unwinds);

                if (req->stub && req->ordering.tempted) {
                        call_stub_destroy (req->stub);
			req->stub = NULL;
                }

		if (req->iobref)
			iobref_unref (req->iobref);

		if (req->fd)
			fd_unref (req->fd);

                GF_FREE (req);
        }
out:
        return ret;
}
