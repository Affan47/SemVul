gppv_dump(GF_Box *a, FILE * trace)
{
	char *szName;
	GF_3GPPVisualSampleEntryBox *p = (GF_3GPPVisualSampleEntryBox *)a;

	switch (p->type) {
	case GF_ISOM_SUBTYPE_3GP_H263: szName = "H263SampleDescription"; break;
	default: szName = "3GPVisualSampleDescription"; break;
	}
	fprintf(trace, "<%sBox", szName);
	base_visual_entry_dump((GF_VisualSampleEntryBox *)p, trace);
	fprintf(trace, ">\n");
	DumpBox(a, trace);
	if (p->info) {
		gf_box_dump(p->info, trace);
	} else {
		fprintf(trace, "<!--INVALID 3GPP FILE: Config not present in Sample Description-->\n");
	}
	gf_box_dump_done(NULL, a, trace);
	fprintf(trace, "</%sBox>\n", szName);
	return GF_OK;
}
