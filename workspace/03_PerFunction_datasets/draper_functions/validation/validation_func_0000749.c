evhttp_htmlescape(const char *html)
{
	size_t i;
	size_t new_size = 0, old_size = 0;
	char *escaped_html, *p;

	if (html == NULL)
		return (NULL);

	old_size = strlen(html);
	for (i = 0; i < old_size; ++i) {
		const char *replaced = NULL;
		const size_t replace_size = html_replace(html[i], &replaced);
		if (replace_size > EV_SIZE_MAX - new_size) {
			event_warn("%s: html_replace overflow", __func__);
			return (NULL);
		}
		new_size += replace_size;
	}

	if (new_size == EV_SIZE_MAX)
		return (NULL);
	p = escaped_html = mm_malloc(new_size + 1);
	if (escaped_html == NULL) {
		event_warn("%s: malloc(%lu)", __func__,
		           (unsigned long)(new_size + 1));
		return (NULL);
	}
	for (i = 0; i < old_size; ++i) {
		const char *replaced = &html[i];
		const size_t len = html_replace(html[i], &replaced);
		memcpy(p, replaced, len);
		p += len;
	}

	*p = '\0';

	return (escaped_html);
}
