imapx_free_body (struct _CamelMessageContentInfo *cinfo)
{
	struct _CamelMessageContentInfo *list, *next;

	list = cinfo->childs;
	while (list) {
		next = list->next;
		imapx_free_body (list);
		list = next;
	}

	if (cinfo->type)
		camel_content_type_unref (cinfo->type);
	g_free (cinfo->id);
	g_free (cinfo->description);
	g_free (cinfo->encoding);
	g_free (cinfo);
}
