create_trust_for_reference (GkmModule *module, GkmManager *manager,
                            CK_ATTRIBUTE_PTR serial, CK_ATTRIBUTE_PTR issuer)
{
	GkmXdgTrust *trust;
	GNode *asn, *ref, *node;
	GBytes *bytes;

	asn = egg_asn1x_create (xdg_asn1_tab, "trust-1");
	g_return_val_if_fail (asn, NULL);

	ref = egg_asn1x_node (asn, "reference", NULL);
	node = egg_asn1x_node (ref, "certReference", NULL);

	egg_asn1x_set_choice (ref, node);
	bytes = g_bytes_new (serial->pValue, serial->ulValueLen);
	egg_asn1x_set_integer_as_raw (egg_asn1x_node (node, "serialNumber", NULL), bytes);
	g_bytes_unref (bytes);

	bytes = g_bytes_new (issuer->pValue, issuer->ulValueLen);
	egg_asn1x_set_any_raw (egg_asn1x_node (node, "issuer", NULL), bytes);
	g_bytes_unref (bytes);

	trust = g_object_new (GKM_XDG_TYPE_TRUST, "module", module, "manager", manager, NULL);
	trust->pv->asn = asn;


	trust->pv->bytes = egg_asn1x_encode (asn, NULL);
	if (!trust->pv->bytes) {
		g_warning ("created invalid trust object: %s", egg_asn1x_message (asn));
		return NULL;
	}

	return trust;
}
