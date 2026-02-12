GF_Err mdia_box_size(GF_Box *s)
{
	u32 pos = 0;
	GF_MediaBox *ptr = (GF_MediaBox *)s;

	gf_isom_check_position(s, (GF_Box*)ptr->mediaHeader, &pos);

	gf_isom_check_position(s, (GF_Box*)ptr->handler, &pos);

#if 0

	GF_Box *elng = gf_isom_box_find_child(ptr->child_boxes, GF_ISOM_BOX_TYPE_ELNG);
	if (elng)
		gf_isom_check_position(s, elng, &pos);
#endif


	gf_isom_check_position(s, (GF_Box*)ptr->information, &pos);
	return GF_OK;
}
