static void hdb_samba4_free_entry_context(krb5_context context, struct HDB *db, hdb_entry *entry)
{


	if (entry->context != NULL) {
		struct samba_kdc_entry *skdc_entry =
			talloc_get_type_abort(entry->context,
			struct samba_kdc_entry);


		entry->context = NULL;
		skdc_entry->kdc_entry = NULL;
		TALLOC_FREE(skdc_entry);
	}
}
