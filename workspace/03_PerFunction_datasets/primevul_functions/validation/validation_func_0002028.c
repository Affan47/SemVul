void gf_isom_box_dump_done(const char *name, GF_Box *ptr, FILE *trace)
{

	skip_box_dump_del = GF_FALSE;
	if (ptr && ptr->other_boxes) {
		gf_isom_box_array_dump(ptr->other_boxes, trace);
	}
	if (name)
		fprintf(trace, "</%s>\n", name);
}
