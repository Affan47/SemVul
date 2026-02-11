ls_lock_v5(dlm_lshandle_t ls,
		uint32_t mode,
		struct dlm_lksb *lksb,
		uint32_t flags,
		const void *name,
		unsigned int namelen,
		uint32_t parent,
		void (*astaddr) (void *astarg),
		void *astarg,
		void (*bastaddr) (void *astarg))
{
	char parambuf[sizeof(struct dlm_write_request_v5) + DLM_RESNAME_MAXLEN];
	struct dlm_write_request_v5 *req = (struct dlm_write_request_v5 *)parambuf;
	struct dlm_ls_info *lsinfo = (struct dlm_ls_info *)ls;
	int status;
	int len;

	memset(req, 0, sizeof(*req));
	set_version_v5(req);

	req->cmd = DLM_USER_LOCK;
	req->i.lock.mode = mode;
	req->i.lock.flags = (flags & ~LKF_WAIT);
	req->i.lock.lkid = lksb->sb_lkid;
	req->i.lock.parent = parent;
	req->i.lock.lksb = lksb;
	req->i.lock.castaddr = astaddr;
	req->i.lock.bastaddr = bastaddr;
	req->i.lock.castparam = astarg;
	req->i.lock.bastparam = astarg;

	if (flags & LKF_CONVERT) {
		req->i.lock.namelen = 0;
	} else {
		if (namelen > DLM_RESNAME_MAXLEN) {
			errno = EINVAL;
			return -1;
		}
		req->i.lock.namelen = namelen;
		memcpy(req->i.lock.name, name, namelen);
	}

	if (flags & LKF_VALBLK) {
		memcpy(req->i.lock.lvb, lksb->sb_lvbptr, DLM_LVB_LEN);
	}

	len = sizeof(struct dlm_write_request_v5) + namelen;
	lksb->sb_status = EINPROG;

	if (flags & LKF_WAIT)
		status = sync_write_v5(lsinfo, req, len);
	else
		status = write(lsinfo->fd, req, len);

	if (status < 0)
		return -1;


	if (status > 0)
		lksb->sb_lkid = status;
	return 0;
}
