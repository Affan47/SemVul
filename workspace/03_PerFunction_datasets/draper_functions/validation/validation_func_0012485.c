_destroy_part_sub(void *object)
{
	sview_part_sub_t *sview_part_sub = (sview_part_sub_t *)object;

	if (sview_part_sub) {
		xfree(sview_part_sub->features);
		xfree(sview_part_sub->reason);
		if (sview_part_sub->hl)
			hostlist_destroy(sview_part_sub->hl);
		if (sview_part_sub->node_ptr_list)
			list_destroy(sview_part_sub->node_ptr_list);
		xfree(sview_part_sub);
	}
}
