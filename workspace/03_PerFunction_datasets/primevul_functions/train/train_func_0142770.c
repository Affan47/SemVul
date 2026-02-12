userptr_mn_invalidate_range_start(struct mmu_notifier *_mn,
				  const struct mmu_notifier_range *range)
{
	struct i915_mmu_notifier *mn =
		container_of(_mn, struct i915_mmu_notifier, mn);
	struct interval_tree_node *it;
	unsigned long end;
	int ret = 0;

	if (RB_EMPTY_ROOT(&mn->objects.rb_root))
		return 0;


	end = range->end - 1;

	spin_lock(&mn->lock);
	it = interval_tree_iter_first(&mn->objects, range->start, end);
	while (it) {
		struct drm_i915_gem_object *obj;

		if (!mmu_notifier_range_blockable(range)) {
			ret = -EAGAIN;
			break;
		}


		obj = container_of(it, struct i915_mmu_object, it)->obj;
		if (!kref_get_unless_zero(&obj->base.refcount)) {
			it = interval_tree_iter_next(it, range->start, end);
			continue;
		}
		spin_unlock(&mn->lock);

		ret = i915_gem_object_unbind(obj,
					     I915_GEM_OBJECT_UNBIND_ACTIVE |
					     I915_GEM_OBJECT_UNBIND_BARRIER);
		if (ret == 0)
			ret = __i915_gem_object_put_pages(obj);
		i915_gem_object_put(obj);
		if (ret)
			return ret;

		spin_lock(&mn->lock);


		it = interval_tree_iter_first(&mn->objects, range->start, end);
	}
	spin_unlock(&mn->lock);

	return ret;

}
