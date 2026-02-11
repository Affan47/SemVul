e_soap_parameter_get_property (ESoapParameter *param,
                               const gchar *prop_name)
{
	xmlChar *xml_s;
	gchar *s;

	g_return_val_if_fail (param != NULL, NULL);
	g_return_val_if_fail (prop_name != NULL, NULL);

	xml_s = xmlGetProp (param, (const xmlChar *) prop_name);
	s = g_strdup ((gchar *) xml_s);
	xmlFree (xml_s);

	return s;
}
