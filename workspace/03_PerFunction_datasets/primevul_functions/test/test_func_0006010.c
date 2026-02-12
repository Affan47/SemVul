static u32 do_import_sub()
{


#ifndef GPAC_DISABLE_MEDIA_IMPORT
	GF_Err e;
	GF_MediaImporter import;

	file = gf_isom_open("ttxt_convert", GF_ISOM_OPEN_WRITE, NULL);
	if (timescale && file) gf_isom_set_timescale(file, timescale);

	memset(&import, 0, sizeof(GF_MediaImporter));
	import.dest = file;
	import.in_name = inName;

	e = gf_media_import(&import);
	if (e) {
		M4_LOG(GF_LOG_ERROR, ("Error importing %s: %s\n", inName, gf_error_to_string(e)));
		gf_isom_delete(file);
		gf_file_delete("ttxt_convert");
		return mp4box_cleanup(1);
	}

	strcpy(outfile, inName);
	if (strchr(outfile, '.')) {
		while (outfile[strlen(outfile)-1] != '.') outfile[strlen(outfile)-1] = 0;
		outfile[strlen(outfile)-1] = 0;
	}
#ifndef GPAC_DISABLE_ISOM_DUMP

	dump_isom_timed_text(file, gf_isom_get_track_id(file, 1),
						  dump_std ? NULL : (outName ? outName : outfile), outName ? GF_TRUE : GF_FALSE,
						  GF_TRUE,
						  (import_subtitle==2) ? GF_TEXTDUMPTYPE_SVG : (dump_srt ? GF_TEXTDUMPTYPE_SRT : GF_TEXTDUMPTYPE_TTXT));
#endif

	gf_isom_delete(file);
	gf_file_delete("ttxt_convert");
	if (e) {
		M4_LOG(GF_LOG_ERROR, ("Error converting %s: %s\n", inName, gf_error_to_string(e)));
		return mp4box_cleanup(1);
	}
	return mp4box_cleanup(0);
#else
	M4_LOG(GF_LOG_ERROR, ("Feature not supported\n"));
	return mp4box_cleanup(1);
#endif
}
