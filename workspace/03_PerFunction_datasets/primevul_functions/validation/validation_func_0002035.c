void gf_isom_box_del(GF_Box *a)
{
	GF_List *other_boxes;
	if (!a) return;
	if (skip_box_dump_del) return;

	other_boxes	= a->other_boxes;
	a->other_boxes = NULL;

	if (!a->registry) {
		GF_LOG(GF_LOG_ERROR, GF_LOG_CONTAINER, ("[iso file] Delete invalid box type %s without registry\n", gf_4cc_to_str(a->type) ));
	} else {
		if (use_dump_mode) {
			skip_box_dump_del = GF_TRUE;
			a->registry->del_fn(a);
			skip_box_dump_del = GF_FALSE;
		} else {
			a->registry->del_fn(a);
		}
	}

	if (other_boxes) {
		gf_isom_box_array_del(other_boxes);
	}
}
