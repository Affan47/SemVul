ab_apply(FormStack *st, Fixed space, u32 *group_idx, u32 count)
{
	Fixed min_y;
	u32 i, start;
	GF_Rect *rc;

	start = 0;
	rc = &form_get_group(st, group_idx[0])->final;
	min_y = rc->y - rc->height;
	if(space>-FIX_ONE) {
		start = 1;
		min_y += space;
	} else {
		for (i=1; i<count; i++) {
			rc = &form_get_group(st, group_idx[i])->final;
			if (group_idx[i]==0) {
				min_y = rc->y - rc->height;
				break;
			}
			if (rc->y - rc->height < min_y) min_y = rc->y - rc->height;
		}
	}
	for (i=start; i<count; i++) {
		if(group_idx[i] == 0) continue;
		rc = &form_get_group(st, group_idx[i])->final;
		rc->y = min_y + rc->height;
		fg_update_bounds(form_get_group(st, group_idx[i]));
	}
}
