validate_exec_list(struct drm_device *dev,
		   struct drm_i915_gem_exec_object2 *exec,
		   int count)
{
	unsigned relocs_total = 0;
	unsigned relocs_max = UINT_MAX / sizeof(struct drm_i915_gem_relocation_entry);
	unsigned invalid_flags;
	int i;

	invalid_flags = __EXEC_OBJECT_UNKNOWN_FLAGS;
	if (USES_FULL_PPGTT(dev))
		invalid_flags |= EXEC_OBJECT_NEEDS_GTT;

	for (i = 0; i < count; i++) {
		char __user *ptr = to_user_ptr(exec[i].relocs_ptr);
		int length;

		if (exec[i].flags & invalid_flags)
			return -EINVAL;


		if (exec[i].flags & EXEC_OBJECT_PINNED) {
			if (exec[i].offset !=
			    gen8_canonical_addr(exec[i].offset & PAGE_MASK))
				return -EINVAL;


			exec[i].offset = gen8_noncanonical_addr(exec[i].offset);
		}

		if (exec[i].alignment && !is_power_of_2(exec[i].alignment))
			return -EINVAL;


		if (exec[i].relocation_count > relocs_max - relocs_total)
			return -EINVAL;
		relocs_total += exec[i].relocation_count;

		length = exec[i].relocation_count *
			sizeof(struct drm_i915_gem_relocation_entry);


		if (!access_ok(VERIFY_WRITE, ptr, length))
			return -EFAULT;

		if (likely(!i915.prefault_disable)) {
			if (fault_in_multipages_readable(ptr, length))
				return -EFAULT;
		}
	}

	return 0;
}
