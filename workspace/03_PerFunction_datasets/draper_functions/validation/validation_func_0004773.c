date_getter (EContact *contact,
             EVCardAttribute *attr)
{
	if (attr) {
		GList *p = e_vcard_attribute_get_values (attr);
		EContactDate *date;

		if (p && p->data && ((gchar *) p->data)[0])
			date = e_contact_date_from_string ((gchar *) p->data);
		else
			date = NULL;

		return date;
	}

	return NULL;
}
