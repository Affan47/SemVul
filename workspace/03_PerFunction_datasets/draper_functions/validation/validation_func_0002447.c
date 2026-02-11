amdgpu_vm_get_pt_bos(struct amdgpu_vm *vm, struct list_head *duplicates)
{
	unsigned i;


	for (i = 0; i <= vm->max_pde_used; ++i) {
		struct amdgpu_bo_list_entry *entry = &vm->page_tables[i].entry;

		if (!entry->robj)
			continue;

		list_add(&entry->tv.head, duplicates);
	}

}
