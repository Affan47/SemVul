dump_certificate (GckAttributes *attrs, const gchar *filename)
{
	const GckAttribute *attr;
	GcrCertificate *cert;
	gchar *subject;
	gulong klass;

	if (!gck_attributes_find_ulong (attrs, CKA_CLASS, &klass) ||
	    klass != CKO_CERTIFICATE)
		return FALSE;

	attr = gck_attributes_find (attrs, CKA_VALUE);
	if (!attr)
		return FALSE;

	cert = gcr_simple_certificate_new_static (attr->value, attr->length);
	subject = gcr_certificate_get_subject_dn (cert);
	g_print ("%s: parsed certificate: %s\n", filename, subject);
	g_free (subject);
	g_object_unref (cert);

	return TRUE;
}
