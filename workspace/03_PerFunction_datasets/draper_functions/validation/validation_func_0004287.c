FindNeighborInGroup(ProxyWindow* instigator,
	int not_iconified)
{
	ProxyWindow *proxy;

	if(!instigator)
	{
		return NULL;
	}

#if PROXY_GROUP_DEBUG
	fprintf(stderr,"FindNeighborInGroup %p %p desk %d group %d\n",
		instigator,instigator->proxy_group,instigator->desk,
		instigator->group);
#endif

	for (proxy=firstProxy; proxy != NULL; proxy=proxy->next)
	{
#if PROXY_GROUP_DEBUG
		fprintf(stderr," vs %p %p desk %d group %d\n",
			proxy,proxy->proxy_group,proxy->desk,proxy->group);
#endif
		if (proxy!= instigator && proxy->desk == instigator->desk &&
			proxy->group &&
			proxy->group==instigator->group &&
			(!not_iconified || !proxy->flags.is_iconified))
		{
			return proxy;
		}
	}

	return NULL;
}
