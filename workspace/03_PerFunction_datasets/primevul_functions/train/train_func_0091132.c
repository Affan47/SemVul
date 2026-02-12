static void gf_m2ts_reset_sections(GF_List *sections)
{
	u32 count;
	GF_M2TS_Section *section;


	count = gf_list_count(sections);
	while (count) {
		section = gf_list_get(sections, 0);
		gf_list_rem(sections, 0);
		if (section->data) gf_free(section->data);
		gf_free(section);
		count--;
	}
}
