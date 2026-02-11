use_mppe_toggled_cb (GtkToggleButton *widget, CEPagePpp *self)
{
	CEPagePppPrivate *priv = CE_PAGE_PPP_GET_PRIVATE (self);

	if (gtk_toggle_button_get_active (widget)) {
		gtk_widget_set_sensitive (GTK_WIDGET (priv->mppe_require_128), TRUE);
		gtk_widget_set_sensitive (GTK_WIDGET (priv->use_mppe_stateful), TRUE);
	} else {
		gtk_widget_set_sensitive (GTK_WIDGET (priv->mppe_require_128), FALSE);
		gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (priv->mppe_require_128), FALSE);
		gtk_widget_set_sensitive (GTK_WIDGET (priv->use_mppe_stateful), FALSE);
		gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (priv->use_mppe_stateful), FALSE);
	}

	ce_page_changed (CE_PAGE (self));
}
