compare_single_value (EVCard *vcard,
                      const gchar *attrname,
                      const gchar *expected_value)
{
	EVCardAttribute *attr;
	gchar *str;

	g_return_val_if_fail (vcard != NULL, FALSE);
	g_return_val_if_fail (attrname != NULL, FALSE);
	g_return_val_if_fail (expected_value != NULL, FALSE);

	attr = e_vcard_get_attribute (vcard, attrname);
	g_return_val_if_fail (attr != NULL, FALSE);

	str = e_vcard_attribute_get_value (attr);
	g_return_val_if_fail (str != NULL, FALSE);
	g_return_val_if_fail (g_strcmp0 (str, expected_value) == 0, FALSE);

	g_free (str);

	return TRUE;
}
