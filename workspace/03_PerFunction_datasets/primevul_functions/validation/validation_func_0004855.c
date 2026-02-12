GF_Err mdia_box_size(GF_Box *s)
{
	u32 pos = 0;
	GF_MediaBox *ptr = (GF_MediaBox *)s;

	gf_isom_check_position(s, (GF_Box*)ptr->mediaHeader, &pos);

	gf_isom_check_position(s, (GF_Box*)ptr->handler, &pos);

	gf_isom_check_position(s, (GF_Box*)ptr->information, &pos);
	return GF_OK;
}
