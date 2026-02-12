eb_relocate_entry(struct i915_execbuffer *eb,
		  struct i915_vma *vma,
		  const struct drm_i915_gem_relocation_entry *reloc)
{
	struct i915_vma *target;
	int err;


	target = eb_get_vma(eb, reloc->target_handle);
	if (unlikely(!target))
		return -ENOENT;


	if (unlikely(reloc->write_domain & (reloc->write_domain - 1))) {
		DRM_DEBUG("reloc with multiple write domains: "
			  "target %d offset %d "
			  "read %08x write %08x",
			  reloc->target_handle,
			  (int) reloc->offset,
			  reloc->read_domains,
			  reloc->write_domain);
		return -EINVAL;
	}
	if (unlikely((reloc->write_domain | reloc->read_domains)
		     & ~I915_GEM_GPU_DOMAINS)) {
		DRM_DEBUG("reloc with read/write non-GPU domains: "
			  "target %d offset %d "
			  "read %08x write %08x",
			  reloc->target_handle,
			  (int) reloc->offset,
			  reloc->read_domains,
			  reloc->write_domain);
		return -EINVAL;
	}

	if (reloc->write_domain) {
		*target->exec_flags |= EXEC_OBJECT_WRITE;


		if (reloc->write_domain == I915_GEM_DOMAIN_INSTRUCTION &&
		    IS_GEN6(eb->i915)) {
			err = i915_vma_bind(target, target->obj->cache_level,
					    PIN_GLOBAL);
			if (WARN_ONCE(err,
				      "Unexpected failure to bind target VMA!"))
				return err;
		}
	}


	if (!DBG_FORCE_RELOC &&
	    gen8_canonical_addr(target->node.start) == reloc->presumed_offset)
		return 0;


	if (unlikely(reloc->offset >
		     vma->size - (eb->reloc_cache.use_64bit_reloc ? 8 : 4))) {
		DRM_DEBUG("Relocation beyond object bounds: "
			  "target %d offset %d size %d.\n",
			  reloc->target_handle,
			  (int)reloc->offset,
			  (int)vma->size);
		return -EINVAL;
	}
	if (unlikely(reloc->offset & 3)) {
		DRM_DEBUG("Relocation not 4-byte aligned: "
			  "target %d offset %d.\n",
			  reloc->target_handle,
			  (int)reloc->offset);
		return -EINVAL;
	}


	*vma->exec_flags &= ~EXEC_OBJECT_ASYNC;


	return relocate_entry(vma, reloc, eb, target);
}
