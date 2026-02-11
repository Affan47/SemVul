dasher_generic_get_components_info(GF_DashSegInput *input, GF_DASHSegmenterOptions *opts)
{
#ifdef GPAC_DISABLE_MEDIA_IMPORT
	return GF_NOT_SUPPORTED;
#else
	u32 i;
	GF_Err e;
	GF_MediaImporter in;
	memset(&in, 0, sizeof(GF_MediaImporter));
	in.flags = GF_IMPORT_PROBE_ONLY;
	in.in_name = (char *)input->file_name;
	e = gf_media_import(&in);
	if (e) return e;

	input->nb_components = in.nb_tracks;
	for (i=0; i<in.nb_tracks; i++) {
		input->components[i].width = in.tk_info[i].video_info.width;
		input->components[i].height = in.tk_info[i].video_info.height;
		input->components[i].media_type = in.tk_info[i].type;
		input->components[i].channels = in.tk_info[i].audio_info.nb_channels;
		input->components[i].sample_rate = in.tk_info[i].audio_info.sample_rate;
		input->components[i].ID = in.tk_info[i].track_num;
		if (in.tk_info[i].lang)
			strcpy(input->components[i].szLang, gf_4cc_to_str(in.tk_info[i].lang) );
		strcpy(input->components[i].szCodec, in.tk_info[i].szCodecProfile);
		input->components[i].fps_denum = 1000;
		input->components[i].fps_num = (u32) (in.tk_info[i].video_info.FPS*1000);
	}
#endif
	return GF_OK;
}
