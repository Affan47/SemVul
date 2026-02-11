stdp_dump(GF_Box *a, FILE * trace)
{
	GF_DegradationPriorityBox *p;
	u32 i;

	p = (GF_DegradationPriorityBox *)a;
	fprintf(trace, "<DegradationPriorityBox EntryCount=\"%d\">\n", p->nb_entries);
	DumpBox(a, trace);
	gf_full_box_dump(a, trace);

	if (!p->priorities) {
		fprintf(trace, "<!--Warning: No Degradation Priority indications-->\n");
	} else {
		for (i=0; i<p->nb_entries; i++) {
			fprintf(trace, "<DegradationPriorityEntry DegradationPriority=\"%d\"/>\n", p->priorities[i]);
		}
	}
	gf_box_dump_done("DegradationPriorityBox", a, trace);
	return GF_OK;
}
