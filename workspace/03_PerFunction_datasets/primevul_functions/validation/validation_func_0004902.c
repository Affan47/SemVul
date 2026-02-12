GF_Err video_sample_entry_box_size(GF_Box *s)
{
	u32 pos=0;
	GF_MPEGVisualSampleEntryBox *ptr = (GF_MPEGVisualSampleEntryBox *)s;
	gf_isom_video_sample_entry_size((GF_VisualSampleEntryBox *)s);


	gf_isom_check_position(s, (GF_Box *)ptr->esd, &pos);
	gf_isom_check_position(s, (GF_Box *)ptr->cfg_3gpp, &pos);

	gf_isom_check_position(s, (GF_Box *)ptr->avc_config, &pos);
	gf_isom_check_position(s, (GF_Box *)ptr->svc_config, &pos);
	if (ptr->mvc_config) {
		gf_isom_check_position(s, gf_isom_box_find_child(s->child_boxes, GF_ISOM_BOX_TYPE_VWID), &pos);
		gf_isom_check_position(s, (GF_Box *)ptr->mvc_config, &pos);
	}


	gf_isom_check_position(s, (GF_Box *)ptr->hevc_config, &pos);
	gf_isom_check_position(s, (GF_Box *)ptr->lhvc_config, &pos);


	gf_isom_check_position(s, (GF_Box *)ptr->av1_config, &pos);


	gf_isom_check_position(s, (GF_Box *)ptr->vp_config, &pos);


	gf_isom_check_position(s, (GF_Box *)ptr->jp2h, &pos);


	gf_isom_check_position(s, (GF_Box *)ptr->dovi_config, &pos);

	return GF_OK;
}
