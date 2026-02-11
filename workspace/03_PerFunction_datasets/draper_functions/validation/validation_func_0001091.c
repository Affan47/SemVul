brasero_uri_container_get_selected_uris (BraseroURIContainer *container)
{
	BraseroURIContainerIFace *iface;

	g_return_val_if_fail (BRASERO_IS_URI_CONTAINER (container), NULL);

	if (!gtk_widget_get_mapped (GTK_WIDGET (container)))
		return NULL;

	iface = BRASERO_URI_CONTAINER_GET_IFACE (container);
	if (iface->get_selected_uris)
		return (* iface->get_selected_uris) (container);

	return NULL;
}
