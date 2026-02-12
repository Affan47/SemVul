GF_Err ilst_item_box_size(GF_Box *s)
{
	GF_ListItemBox *ptr = (GF_ListItemBox *)s;


	if (ptr->child_boxes && !ptr->data) {
	}

	else if (ptr->data && !ptr->data->qt_style) {
		u32 pos=0;
		gf_isom_check_position(s, (GF_Box* ) ptr->data, &pos);
	}

	else if (ptr->data) {
		ptr->size += ptr->data->dataSize + 4;
	}
	return GF_OK;
}
