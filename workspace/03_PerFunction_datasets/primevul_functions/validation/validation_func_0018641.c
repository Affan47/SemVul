static void __unregister_enc_region_locked(struct kvm *kvm,
					   struct enc_region *region)
{


	sev_clflush_pages(region->pages, region->npages);

	sev_unpin_memory(kvm, region->pages, region->npages);
	list_del(&region->list);
	kfree(region);
}
