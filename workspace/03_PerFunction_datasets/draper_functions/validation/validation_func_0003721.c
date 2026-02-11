get_line_type_from_ref(const struct ref *ref)
{
	if (ref->head)
		return LINE_MAIN_HEAD;
	else if (ref->ltag)
		return LINE_MAIN_LOCAL_TAG;
	else if (ref->tag)
		return LINE_MAIN_TAG;
	else if (ref->tracked)
		return LINE_MAIN_TRACKED;
	else if (ref->remote)
		return LINE_MAIN_REMOTE;
	else if (ref->replace)
		return LINE_MAIN_REPLACE;

	return LINE_MAIN_REF;
}
