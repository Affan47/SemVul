e_filter_part_build_code (EFilterPart *part,
                          GString *out)
{
	GList *link;

	g_return_if_fail (E_IS_FILTER_PART (part));
	g_return_if_fail (out != NULL);

	if (part->code != NULL)
		e_filter_part_expand_code (part, part->code, out);

	for (link = part->elements; link != NULL; link = g_list_next (link)) {
		EFilterElement *element = link->data;
		e_filter_element_build_code (element, out, part);
	}
}
