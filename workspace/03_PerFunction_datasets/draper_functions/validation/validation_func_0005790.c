ebews_vcards_append_dl (EBookBackendEws *ebews,
			const EwsId *id,
                        const gchar *d_name,
                        GSList *members,
                        GSList **vcards,
			GError **error)
{
	EContact *contact;
	EVCardAttribute *attr;
	gchar *vcard_string = NULL;

	contact = ebews_get_dl_info (ebews, id, d_name, members, error);
	if (contact == NULL)
		return;

	attr = e_vcard_attribute_new (NULL, "X-EWS-KIND");
	e_vcard_add_attribute_with_value (E_VCARD (contact), attr, "DT_DISTLIST");

	vcard_string = e_vcard_to_string (E_VCARD (contact), EVC_FORMAT_VCARD_30);
	*vcards = g_slist_append (*vcards, g_strdup(vcard_string));

	g_free (vcard_string);
	g_object_unref (contact);
}
