visit_ignore(const XmlNode *child, gpointer user)
{
	const gchar	*text;

	if(xml_get_text(child, "ignore", &text))
		cng_ignore(&((MainInfo *) user)->cfg.nag, text);
}
