static int rt6_mtu_change_route(struct rt6_info *rt, void *p_arg)
{
	struct rt6_mtu_change_arg *arg = (struct rt6_mtu_change_arg *) p_arg;
	struct inet6_dev *idev;


	idev = __in6_dev_get(arg->dev);
	if (!idev)
		return 0;


	if (rt->dst.dev == arg->dev &&
	    !dst_metric_locked(&rt->dst, RTAX_MTU) &&
	    (dst_mtu(&rt->dst) >= arg->mtu ||
	     (dst_mtu(&rt->dst) < arg->mtu &&
	      dst_mtu(&rt->dst) == idev->cnf.mtu6))) {
		dst_metric_set(&rt->dst, RTAX_MTU, arg->mtu);
	}
	return 0;
}
