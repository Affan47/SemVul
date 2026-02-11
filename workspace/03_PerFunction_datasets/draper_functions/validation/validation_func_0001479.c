e_mail_config_summary_page_set_identity_source (EMailConfigSummaryPage *page,
                                                ESource *identity_source)
{
	g_return_if_fail (E_IS_MAIL_CONFIG_SUMMARY_PAGE (page));

	if (page->priv->identity_source == identity_source)
		return;

	if (identity_source != NULL) {
		g_return_if_fail (E_IS_SOURCE (identity_source));
		g_object_ref (identity_source);
	}

	if (page->priv->identity_source != NULL) {
		g_signal_handler_disconnect (
			page->priv->identity_source,
			page->priv->identity_source_changed_id);
		g_object_unref (page->priv->identity_source);
	}

	page->priv->identity_source = identity_source;
	page->priv->identity_source_changed_id = 0;

	if (identity_source != NULL) {
		gulong handler_id;

		handler_id = g_signal_connect (
			identity_source, "changed",
			G_CALLBACK (mail_config_summary_page_source_changed),
			page);

		page->priv->identity_source_changed_id = handler_id;
	}

	g_object_notify (G_OBJECT (page), "identity-source");

	e_mail_config_summary_page_refresh (page);
}
