ec2n_operation(struct group *grp, ec2np_ptr d, ec2np_ptr a, ec2np_ptr e)
{
	b2n_ptr         ex = e->x;
	struct ec2n_group *group = (struct ec2n_group *)grp->group;

	if (a->y->chunks == 0)
		if (ec2np_find_y(a, group->grp))
			return -1;

	return ec2np_mul(d, a, ex, group->grp);
}
