static void sysfs_slab_remove_workfn(struct work_struct *work)
{
	struct kmem_cache *s =
		container_of(work, struct kmem_cache, kobj_remove_work);

	if (!s->kobj.state_in_sysfs)


		goto out;

#ifdef CONFIG_MEMCG
	kset_unregister(s->memcg_kset);
#endif
	kobject_uevent(&s->kobj, KOBJ_REMOVE);
out:
	kobject_put(&s->kobj);
}
