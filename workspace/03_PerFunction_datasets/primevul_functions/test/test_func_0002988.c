GF_Err moof_box_size(GF_Box *s)
{
	u32 pos=0;
	GF_MovieFragmentBox *ptr = (GF_MovieFragmentBox *) s;
	if (!s) return GF_BAD_PARAM;

	gf_isom_check_position(s, (GF_Box *)ptr->mfhd, &pos);

	gf_isom_check_position_list(s, ptr->PSSHs, &pos);

	gf_isom_check_position_list(s, ptr->TrackList, &pos);
	return GF_OK;
}
