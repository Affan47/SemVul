static int eb_relocate_vma(struct i915_execbuffer *eb, struct i915_vma *vma)
{
#define N_RELOC(x) ((x) / sizeof(struct drm_i915_gem_relocation_entry))
	struct drm_i915_gem_relocation_entry stack[N_RELOC(512)];
	struct drm_i915_gem_relocation_entry __user *urelocs;
	const struct drm_i915_gem_exec_object2 *entry = exec_entry(eb, vma);
	unsigned int remain;

	urelocs = u64_to_user_ptr(entry->relocs_ptr);
	remain = entry->relocation_count;
	if (unlikely(remain > N_RELOC(ULONG_MAX)))
		return -EINVAL;


	if (unlikely(!access_ok(urelocs, remain*sizeof(*urelocs))))
		return -EFAULT;

	do {
		struct drm_i915_gem_relocation_entry *r = stack;
		unsigned int count =
			min_t(unsigned int, remain, ARRAY_SIZE(stack));
		unsigned int copied;


		pagefault_disable();
		copied = __copy_from_user_inatomic(r, urelocs, count * sizeof(r[0]));
		pagefault_enable();
		if (unlikely(copied)) {
			remain = -EFAULT;
			goto out;
		}

		remain -= count;
		do {
			u64 offset = eb_relocate_entry(eb, vma, r);

			if (likely(offset == 0)) {
			} else if ((s64)offset < 0) {
				remain = (int)offset;
				goto out;
			} else {


				offset = gen8_canonical_addr(offset & ~UPDATE);
				if (unlikely(__put_user(offset, &urelocs[r-stack].presumed_offset))) {
					remain = -EFAULT;
					goto out;
				}
			}
		} while (r++, --count);
		urelocs += ARRAY_SIZE(stack);
	} while (remain);
out:
	reloc_cache_reset(&eb->reloc_cache);
	return remain;
}
