nma_mobile_providers_database_lookup_3gpp_mcc_mnc (NMAMobileProvidersDatabase *self,
                                                   const gchar *mccmnc)
{
	GHashTableIter iter;
	gpointer value;
	GSList *piter;
	NMAMobileProvider *provider_match_2mnc = NULL;
	guint mccmnc_len;

	g_return_val_if_fail (NMA_IS_MOBILE_PROVIDERS_DATABASE (self), NULL);
	g_return_val_if_fail (mccmnc != NULL, NULL);

	g_return_val_if_fail (self->priv->countries != NULL, NULL);


	mccmnc_len = strlen (mccmnc);
	if (mccmnc_len != 5 && mccmnc_len != 6)
		return NULL;

	g_hash_table_iter_init (&iter, self->priv->countries);

	while (g_hash_table_iter_next (&iter, NULL, &value)) {
		NMACountryInfo *country_info = value;


		for (piter = nma_country_info_get_providers (country_info);
		     piter;
		     piter = g_slist_next (piter)) {
			NMAMobileProvider *provider = piter->data;
			const gchar **mccmnc_list;
			guint i;


			mccmnc_list = nma_mobile_provider_get_3gpp_mcc_mnc (provider);
			if (!mccmnc_list)
				continue;

			for (i = 0; mccmnc_list[i]; i++) {
				const gchar *mccmnc_iter;
				guint mccmnc_iter_len;

				mccmnc_iter = mccmnc_list[i];
				mccmnc_iter_len = strlen (mccmnc_iter);


				if (strncmp (mccmnc_iter, mccmnc, 3))

					continue;


				if (mccmnc_iter_len == 6) {

					if (   (mccmnc_len == 6 && !strncmp (mccmnc + 3, mccmnc_iter + 3, 3))
					    || (mccmnc_len == 5 && mccmnc_iter[3] == '0' && !strncmp (mccmnc + 3, mccmnc_iter + 4, 2)))

						return provider;


					continue;
				}

				if (   !provider_match_2mnc
				    && mccmnc_iter_len == 5) {
					if (   (mccmnc_len == 5 && !strncmp (mccmnc + 3, mccmnc_iter + 3, 2))
					    || (mccmnc_len == 6 && mccmnc[3] == '0' && !strncmp (mccmnc + 4, mccmnc_iter + 3, 2))) {


						provider_match_2mnc = provider;
						continue;
					}


					continue;
				}
			}
		}
	}

	return provider_match_2mnc;
}
