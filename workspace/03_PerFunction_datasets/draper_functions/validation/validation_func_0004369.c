pcrb_Size(GF_Box *s)
{
	GF_Err e;
	GF_PcrInfoBox *ptr = (GF_PcrInfoBox*) s;
	e = gf_isom_box_get_size(s);
	if (e) return e;

	ptr->size += 4;
	ptr->size += ptr->subsegment_count * 8;

	return GF_OK;
}
