cap_capable(const struct cred *cred, struct user_namespace *targ_ns,
		int cap, int audit)
{
	struct user_namespace *ns = targ_ns;


	for (;;) {

		if (ns == cred->user_ns)
			return cap_raised(cred->cap_effective, cap) ? 0 : -EPERM;


		if (ns == &init_user_ns)
			return -EPERM;


		if ((ns->parent == cred->user_ns) && uid_eq(ns->owner, cred->euid))
			return 0;


		ns = ns->parent;
	}


}
