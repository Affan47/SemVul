pmap_remove(struct pmap *pm, const void *p, size_t size)
{
	struct vm_fragment *vmf;

	g_assert(round_pagesize_fast(size) == size);

	mutex_lock(&pm->lock);

	vmf = pmap_lookup(pm, p, NULL);

	if (vmf != NULL) {
		const void *end = const_ptr_add_offset(p, size);
		const void *vend = vmf->end;

		g_assert(vmf_size(vmf) >= size);

		if (p == vmf->start) {

			if (vmm_debugging(2)) {
				s_debug("VMM %s %zuKiB region at %p was %s fragment",
					vmf_type_str(vmf->type), size / 1024, p,
					end == vend ? "a whole" : "start of a");
			}

			if (end == vend) {
				pmap_remove_whole_region(pm, p, size);
			} else {
				vmf->start = end;
				vmf->mtime = tm_time();
				g_assert(ptr_cmp(vmf->start, vend) < 0);
			}
		} else {
			g_assert(ptr_cmp(vmf->start, p) < 0);
			g_assert(ptr_cmp(end, vend) <= 0);

			vmf->end = p;
			vmf->mtime = tm_time();

			if (end != vend) {
				if (vmm_debugging(1)) {
					s_debug("VMM freeing %s %zuKiB region at %p "
						"fragments VM space",
						vmf_type_str(vmf->type), size / 1024, p);
				}
				pmap_insert_region(pm, end, ptr_diff(vend, end), vmf->type);
			}
		}
	} else {
		if (vmm_debugging(0)) {
			s_warning("VMM %zuKiB region at %p missing from pmap",
				size / 1024, p);
		}
	}

	mutex_unlock(&pm->lock);
}
