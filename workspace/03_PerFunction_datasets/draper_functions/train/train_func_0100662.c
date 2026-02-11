acpi_memory_remove_memory(struct acpi_memory_device *mem_device)
{
	acpi_handle handle = mem_device->device->handle;
	struct acpi_memory_info *info, *n;
	int nid = acpi_get_node(handle);

	list_for_each_entry_safe(info, n, &mem_device->res_list, list) {
		if (!info->enabled)
			continue;

		if (nid == NUMA_NO_NODE)
			nid = memory_add_physaddr_to_nid(info->start_addr);

		acpi_unbind_memory_blocks(info);
		remove_memory(nid, info->start_addr, info->length);
		list_del(&info->list);
		kfree(info);
	}
}
