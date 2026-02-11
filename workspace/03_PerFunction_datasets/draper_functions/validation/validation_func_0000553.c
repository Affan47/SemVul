nfs4_callback_layoutrecall(struct cb_layoutrecallargs *args,
				  void *dummy, struct cb_process_state *cps)
{
	u32 res;

	dprintk("%s: -->\n", __func__);

	if (cps->clp)
		res = do_callback_layoutrecall(cps->clp, args);
	else
		res = NFS4ERR_OP_NOT_IN_SESSION;

	dprintk("%s: exit with status = %d\n", __func__, res);
	return cpu_to_be32(res);
}
