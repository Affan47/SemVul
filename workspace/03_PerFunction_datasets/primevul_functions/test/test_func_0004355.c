static u32 get_box_reg_idx(u32 boxCode, u32 parent_type, u32 start_from)
{
	u32 i=0, count = gf_isom_get_num_supported_boxes();
	const char *parent_name = parent_type ? gf_4cc_to_str(parent_type) : NULL;

	if (!start_from) start_from = 1;

	for (i=start_from; i<count; i++) {
		u32 start_par_from;
		if (box_registry[i].box_4cc != boxCode)
			continue;

		if (!parent_type)
			return i;
		if (strstr(box_registry[i].parents_4cc, parent_name) != NULL)
			return i;
		if (strstr(box_registry[i].parents_4cc, "*") != NULL)
			return i;

		if (strstr(box_registry[i].parents_4cc, "sample_entry") == NULL)
			continue;


		if (parent_type==GF_QT_SUBTYPE_RAW)
			return i;

		start_par_from = 0;
		while (parent_type) {

			u32 j = get_box_reg_idx(parent_type, 0, start_par_from);
			if (!j) break;

			if (box_registry[j].parents_4cc && (strstr(box_registry[j].parents_4cc, "stsd") != NULL))
				return i;
			start_par_from = j+1;
		}
	}
	return 0;
}
