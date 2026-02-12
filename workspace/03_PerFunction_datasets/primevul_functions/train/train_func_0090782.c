GF_Err gf_media_export(GF_MediaExporter *dumper)
{
	if (!dumper) return GF_BAD_PARAM;
	if (!dumper->out_name && !(dumper->flags & GF_EXPORT_PROBE_ONLY) && !dumper->dump_file) return GF_BAD_PARAM;


#ifndef GPAC_DISABLE_ISOM_WRITE
	if (dumper->flags & GF_EXPORT_MP4) return gf_media_export_isom(dumper);
#endif
#ifndef GPAC_DISABLE_VTT
	else if (dumper->flags & GF_EXPORT_WEBVTT_META) return gf_media_export_webvtt_metadata(dumper);
#endif
	else if (dumper->flags & GF_EXPORT_SIX) return gf_media_export_six(dumper);


	else if (dumper->flags & GF_EXPORT_SAF) return gf_media_export_saf(dumper);


	return gf_media_export_filters(dumper);
}
