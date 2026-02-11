gf_odf_write_lang(GF_BitStream *bs, GF_Language *ld)
{
	GF_Err e;
	u32 size;
	if (!ld) return GF_BAD_PARAM;

	e = gf_odf_size_descriptor((GF_Descriptor *)ld, &size);
	if (e) return e;
	e = gf_odf_write_base_descriptor(bs, ld->tag, size);
	if (e) return e;
	gf_bs_write_int(bs, ld->langCode, 24);
	return GF_OK;
}
