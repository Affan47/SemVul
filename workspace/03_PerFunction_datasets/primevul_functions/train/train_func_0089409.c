GF_Err alis_box_write(GF_Box *s, GF_BitStream *bs)
{
	GF_Err e;


	e = gf_isom_full_box_write(s, bs);
	if (e) return e;
	return GF_OK;
}
