gcr_certificate_get_issuer_name (GcrCertificate *self)
{
	gchar *name;

	name = gcr_certificate_get_issuer_part (self, "cn");
	if (name == NULL)
		name = gcr_certificate_get_issuer_part (self, "ou");
	if (name == NULL)
		name = gcr_certificate_get_issuer_part (self, "o");

	return name;
}
