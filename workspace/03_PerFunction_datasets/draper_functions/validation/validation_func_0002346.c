vxlan_build_gbp_hdr(struct vxlanhdr *vxh, u32 vxflags,
				struct vxlan_metadata *md)
{
	struct vxlanhdr_gbp *gbp;

	if (!md->gbp)
		return;

	gbp = (struct vxlanhdr_gbp *)vxh;
	vxh->vx_flags |= htonl(VXLAN_HF_GBP);

	if (md->gbp & VXLAN_GBP_DONT_LEARN)
		gbp->dont_learn = 1;

	if (md->gbp & VXLAN_GBP_POLICY_APPLIED)
		gbp->policy_applied = 1;

	gbp->policy_id = htons(md->gbp & VXLAN_GBP_ID_MASK);
}
