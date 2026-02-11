ib_uverbs_rereg_mr(struct ib_uverbs_file *file,
			   struct ib_device *ib_dev,
			   const char __user *buf, int in_len,
			   int out_len)
{
	struct ib_uverbs_rereg_mr      cmd;
	struct ib_uverbs_rereg_mr_resp resp;
	struct ib_udata              udata;
	struct ib_pd                *pd = NULL;
	struct ib_mr                *mr;
	struct ib_pd		    *old_pd;
	int                          ret;
	struct ib_uobject	    *uobj;

	if (out_len < sizeof(resp))
		return -ENOSPC;

	if (copy_from_user(&cmd, buf, sizeof(cmd)))
		return -EFAULT;

	INIT_UDATA(&udata, buf + sizeof(cmd),
		   (unsigned long) cmd.response + sizeof(resp),
		   in_len - sizeof(cmd), out_len - sizeof(resp));

	if (cmd.flags & ~IB_MR_REREG_SUPPORTED || !cmd.flags)
		return -EINVAL;

	if ((cmd.flags & IB_MR_REREG_TRANS) &&
	    (!cmd.start || !cmd.hca_va || 0 >= cmd.length ||
	     (cmd.start & ~PAGE_MASK) != (cmd.hca_va & ~PAGE_MASK)))
			return -EINVAL;

	uobj = idr_write_uobj(&ib_uverbs_mr_idr, cmd.mr_handle,
			      file->ucontext);

	if (!uobj)
		return -EINVAL;

	mr = uobj->object;

	if (cmd.flags & IB_MR_REREG_ACCESS) {
		ret = ib_check_mr_access(cmd.access_flags);
		if (ret)
			goto put_uobjs;
	}

	if (cmd.flags & IB_MR_REREG_PD) {
		pd = idr_read_pd(cmd.pd_handle, file->ucontext);
		if (!pd) {
			ret = -EINVAL;
			goto put_uobjs;
		}
	}

	if (atomic_read(&mr->usecnt)) {
		ret = -EBUSY;
		goto put_uobj_pd;
	}

	old_pd = mr->pd;
	ret = mr->device->rereg_user_mr(mr, cmd.flags, cmd.start,
					cmd.length, cmd.hca_va,
					cmd.access_flags, pd, &udata);
	if (!ret) {
		if (cmd.flags & IB_MR_REREG_PD) {
			atomic_inc(&pd->usecnt);
			mr->pd = pd;
			atomic_dec(&old_pd->usecnt);
		}
	} else {
		goto put_uobj_pd;
	}

	memset(&resp, 0, sizeof(resp));
	resp.lkey      = mr->lkey;
	resp.rkey      = mr->rkey;

	if (copy_to_user((void __user *)(unsigned long)cmd.response,
			 &resp, sizeof(resp)))
		ret = -EFAULT;
	else
		ret = in_len;

put_uobj_pd:
	if (cmd.flags & IB_MR_REREG_PD)
		put_pd_read(pd);

put_uobjs:

	put_uobj_write(mr->uobject);

	return ret;
}
