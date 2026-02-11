of_free_overlay_info(struct of_overlay *ov)
{
	struct of_overlay_info *ovinfo;
	int i;


	for (i = ov->count - 1; i >= 0; i--) {
		ovinfo = &ov->ovinfo_tab[i];

		of_node_put(ovinfo->target);
		of_node_put(ovinfo->overlay);
	}
	kfree(ov->ovinfo_tab);

	return 0;
}
