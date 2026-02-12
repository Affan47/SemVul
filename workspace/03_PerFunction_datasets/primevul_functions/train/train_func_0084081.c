static s32 vvc_parse_slice(GF_BitStream *bs, VVCState *vvc, VVCSliceInfo *si)
{


	si->picture_header_in_slice_header_flag = gf_bs_read_int_log(bs, 1, "picture_header_in_slice_header_flag");
	if (si->picture_header_in_slice_header_flag) {
		GF_LOG(GF_LOG_DEBUG, GF_LOG_CODING, ("[VVC] Picture header in slice header incomplete support, cannot guess slice type\n"));
		si->slice_type = GF_VVC_SLICE_TYPE_UNKNOWN;
		return vvc_parse_picture_header(bs, vvc, si);
	}
	if (!si->sps) return -1;
	si->slice_type = GF_VVC_SLICE_TYPE_I;
	if (gf_bs_read_int_log(bs, 1, "sps_subpic_info_present_flag")) {
		gf_bs_read_int_log(bs, si->sps->subpicid_len, "subpic_id");

	}

	if (si->pps->rect_slice_flag ) {
		GF_LOG(GF_LOG_WARNING, GF_LOG_CODING, ("[VVC] tiling parsing not supported - patch welcome\n"));
		return 0;
	}
	gf_bs_read_int_log(bs, si->sps->sh_num_extra_bits, "num_extra_bits");


	if (si->inter_slice_allowed_flag )
		si->slice_type = gf_bs_read_int_log(bs, 2, "slice_type");

	return 0;
}
