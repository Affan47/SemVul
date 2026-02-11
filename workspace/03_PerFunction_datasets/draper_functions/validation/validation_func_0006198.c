test_gd_name_empty_strings (void)
{
	GDataGDName *name;
	GError *error = NULL;

	g_test_bug ("662290");


	name = GDATA_GD_NAME (gdata_parsable_new_from_xml (GDATA_TYPE_GD_NAME,
		"<gd:name xmlns:gd='http://schemas.google.com/g/2005'>"
			"<gd:fullName></gd:fullName>"
		"</gd:name>", -1, &error));
	g_assert_no_error (error);
	g_assert (GDATA_IS_GD_NAME (name));
	g_clear_error (&error);


	g_assert_cmpstr (gdata_gd_name_get_given_name (name), ==, NULL);
	g_assert_cmpstr (gdata_gd_name_get_additional_name (name), ==, NULL);
	g_assert_cmpstr (gdata_gd_name_get_family_name (name), ==, NULL);
	g_assert_cmpstr (gdata_gd_name_get_prefix (name), ==, NULL);
	g_assert_cmpstr (gdata_gd_name_get_suffix (name), ==, NULL);
	g_assert_cmpstr (gdata_gd_name_get_full_name (name), ==, NULL);

	g_object_unref (name);


	name = gdata_gd_name_new ("Georgey", "Porgey");
	gdata_gd_name_set_full_name (name, "");

	g_assert_cmpstr (gdata_gd_name_get_full_name (name), ==, NULL);


	gdata_test_assert_xml (name,
		"<?xml version='1.0' encoding='UTF-8'?>"
		"<gd:name xmlns='http://www.w3.org/2005/Atom' xmlns:gd='http://schemas.google.com/g/2005'>"
			"<gd:givenName>Georgey</gd:givenName>"
			"<gd:familyName>Porgey</gd:familyName>"
		"</gd:name>");

	g_object_unref (name);
}
