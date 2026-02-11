check_boost_vol(struct hda_codec *codec, hda_nid_t nid,
			    int dir, int idx)
{
	unsigned int step;

	if (!nid_has_volume(codec, nid, dir) ||
	    is_ctl_associated(codec, nid, dir, idx, NID_PATH_VOL_CTL) ||
	    is_ctl_associated(codec, nid, dir, idx, NID_PATH_BOOST_CTL))
		return false;

	step = (query_amp_caps(codec, nid, dir) & AC_AMPCAP_STEP_SIZE)
		>> AC_AMPCAP_STEP_SIZE_SHIFT;
	if (step < 0x20)
		return false;
	return true;
}
