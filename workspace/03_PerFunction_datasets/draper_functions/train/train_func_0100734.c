au_call_dpages_append(void *_arg, struct dentry *dentry)
{
	enum d_walk_ret ret;
	struct ac_dpages_arg *arg = _arg;

	ret = D_WALK_CONTINUE;
	if (dentry->d_sb == arg->sb
	    && !IS_ROOT(dentry)
	    && au_dcount(dentry) > 0
	    && au_di(dentry)
	    && (!arg->test || arg->test(dentry, arg->arg))) {
		arg->err = au_dpages_append(arg->dpages, dentry, GFP_ATOMIC);
		if (unlikely(arg->err))
			ret = D_WALK_QUIT;
	}

	return ret;
}
