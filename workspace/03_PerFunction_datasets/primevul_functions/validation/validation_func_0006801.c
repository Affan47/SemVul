static void sysfs_slab_remove(struct kmem_cache *s)
{
	if (slab_state < FULL)


		return;

	kobject_get(&s->kobj);
	schedule_work(&s->kobj_remove_work);
}
