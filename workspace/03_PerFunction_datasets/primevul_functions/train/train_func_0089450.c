GF_Err ilst_item_box_write(GF_Box *s, GF_BitStream *bs)
{
	GF_Err e;
	GF_ListItemBox *ptr = (GF_ListItemBox *) s;

	e = gf_isom_box_write_header(s, bs);
	if (e) return e;


	if (ptr->child_boxes && !ptr->data) {
	}

	else if (!ptr->data->qt_style) {
	}

	else {
		gf_bs_write_u16(bs, ptr->data->dataSize);
		gf_bs_write_u16(bs, 0);
		gf_bs_write_data(bs, ptr->data->data, ptr->data->dataSize);
		ptr->size = 0;
	}
	return GF_OK;
}
