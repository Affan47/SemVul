GF_Err gf_av1_parse_obu_header(GF_BitStream *bs, ObuType *obu_type, Bool *obu_extension_flag, Bool *obu_has_size_field, u8 *temporal_id, u8 *spatial_id)
{
	Bool forbidden = gf_bs_read_int(bs, 1);
	if (forbidden) {
		return GF_NON_COMPLIANT_BITSTREAM;
	}

	*obu_type = gf_bs_read_int(bs, 4);
	*obu_extension_flag = gf_bs_read_int(bs, 1);
	*obu_has_size_field = gf_bs_read_int(bs, 1);
	if (gf_bs_read_int(bs, 1) ) {
		return GF_NON_COMPLIANT_BITSTREAM;
	}
	if (*obu_extension_flag) {
		*temporal_id = gf_bs_read_int(bs, 3);
		*spatial_id = gf_bs_read_int(bs, 2);
		gf_bs_read_int(bs, 3);
	}

	return GF_OK;
}
