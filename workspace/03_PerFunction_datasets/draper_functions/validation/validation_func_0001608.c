vmpressure(gfp_t gfp, struct mem_cgroup *memcg,
		unsigned long scanned, unsigned long reclaimed)
{
	struct vmpressure *vmpr = memcg_to_vmpressure(memcg);


	if (!(gfp & (__GFP_HIGHMEM | __GFP_MOVABLE | __GFP_IO | __GFP_FS)))
		return;


	if (!scanned)
		return;

	spin_lock(&vmpr->sr_lock);
	vmpr->scanned += scanned;
	vmpr->reclaimed += reclaimed;
	scanned = vmpr->scanned;
	spin_unlock(&vmpr->sr_lock);

	if (scanned < vmpressure_win)
		return;
	schedule_work(&vmpr->work);
}
