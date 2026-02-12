action_tag_list_xml (ExifData *ed, ExifParams p)
{
	if (!ed) return;

	fprintf(stdout, "<exif>\n");
	if (p.ifd < EXIF_IFD_COUNT)

		show_xml(ed->ifd[p.ifd], &p.use_ids);
	else

		exif_data_foreach_content (ed, show_xml, &p.use_ids);
	fprintf(stdout, "</exif>\n");
}
