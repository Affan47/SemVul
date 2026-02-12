static bool is_unsync_root(hpa_t root)
{
	struct kvm_mmu_page *sp;

	if (!VALID_PAGE(root))
		return false;


	smp_rmb();
	sp = to_shadow_page(root);


	if (WARN_ON_ONCE(!sp))
		return false;

	if (sp->unsync || sp->unsync_children)
		return true;

	return false;
}
