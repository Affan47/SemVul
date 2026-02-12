asmlinkage long sys_getgroups(int gidsetsize, gid_t __user *grouplist)
{
	int i = 0;


	if (gidsetsize < 0)
		return -EINVAL;


	i = current->group_info->ngroups;
	if (gidsetsize) {
		if (i > gidsetsize) {
			i = -EINVAL;
			goto out;
		}
		if (groups_to_user(grouplist, current->group_info)) {
			i = -EFAULT;
			goto out;
		}
	}
out:
	return i;
}
